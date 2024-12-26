#include "inv_index.h"


// MARK: TODO: 后续将 db 的 Iterator 封装成 RAII 类便捷遍历
/*
倒排索引开始
*/
InvIndex::InvIndex(std::string const &db_name,
            bool const &create_if_missing) : size(0) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status =
        leveldb::DB::Open(options, ROOT_PATH + db_name, &db);
    if (not status.ok()) {
        LOG();
        throw std::runtime_error(status.ToString());
    }
}

InvIndex::~InvIndex() {
    delete db;
}

std::optional<InvIndex::size_type> InvIndex::putBatch(DocWordsWithId const &doc) {
    leveldb::WriteBatch batch;
    size_type doc_id = doc.id;
    std::vector<std::string> doc_words(doc.doc_words);
    std::sort(doc_words.begin(), doc_words.end());
    auto end = std::unique(doc_words.begin(), doc_words.end());    

    for (auto it = doc_words.begin(); it != end; ++it) {
        std::string ids;
        auto status = db->Get(leveldb::ReadOptions(), *it, &ids);
        if (status.IsNotFound()) {
            fmt::print("键值对不存在，开始插入: {}: {}\n", *it, doc_id);
            // 不存在时, 直接插进去
            batch.Put(*it, std::to_string(doc_id));
            size += 1;
        } else if (!status.ok()) {
            LOG();
            fmt::print("获取键值对失失败{}\n", status.ToString());
            return std::nullopt;
        } else {
            ids += " " + std::to_string(doc_id); 
            batch.Put(*it, ids);
        }
    }
    auto status = db->Write(leveldb::WriteOptions(), &batch);
    return checkStatus(status, doc.doc_words.size());
}

std::optional<InvIndex::size_type> InvIndex::putSingle(std::pair<std::string, size_type> const &single_word) {
    std::string ids;
    std::set<size_type> vec_id;
    auto status = db->Get(leveldb::ReadOptions(), single_word.first, &ids);
    // 未找到之外的异常状态直接返回
    if (!status.ok() && !status.IsNotFound()) {
        LOG();
        fmt::print("获取键值对失失败{}\n", status.ToString());
        return std::nullopt;
    }

    if (status.IsNotFound()) {
        vec_id.insert(single_word.second);
    } else {
        vec_id = deserializeSet(ids);
        vec_id.insert(single_word.second);
    }

    ids = serializeSet(vec_id);
    status =
        db->Put(leveldb::WriteOptions(), single_word.first, ids);
    return checkStatus(status, 1);
}

// 通过单个单词寻找索引，若是没找到或是为空（原则上不可能为空）则返回 nullopt
std::optional<std::set<InvIndex::size_type>> InvIndex::getSingle(std::string const &word) {
    leveldb::Status status;
    std::string val;
    status = db->Get(leveldb::ReadOptions(), word, &val);
    auto result = deserializeSet(val);
    if (result.empty()) {
        return std::nullopt;
    }
    return checkStatus(status, result);
}

// 通过词语获取一系列文档列表, 由于是通过 words 中的 word 获取，因此不使用迭代器
std::optional<std::map<std::string, std::set<InvIndex::size_type>>> InvIndex::getByWords(std::set<std::string> const& words) {
    std::map<std::string, std::set<size_type>> retMap;
    for (auto const& word : words) {
        auto ids = getSingle(word);
        if (ids.has_value()) {
            retMap[word] = ids.value();
        } else {
            retMap[word] = std::set<size_type>();
        }
    }
    if (retMap.empty()) {
        LOG();
        return std::nullopt;
    }
    return { retMap };
}

// 获取前 n 个索引
std::optional<std::map<std::string, std::set<InvIndex::size_type>>> InvIndex::getInvIndexNCnt(size_type const& count) {
    std::map<std::string, std::set<size_type>> retMap;
    size_type cnt {0};
    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid() and cnt < count; it->Next()) {
        retMap[it->key().ToString()] = deserializeSet(it->value().ToString());
        cnt++;
    }
    delete it;
    if (retMap.empty()) {
        LOG();
        return std::nullopt;
    }
    return { retMap };
}

std::string InvIndex::serializeSet(std::set<size_type> const &vec) {
    std::string binary;
    binary.reserve(vec.size() * sizeof(size_type));
    for (auto &elem: vec) {
        binary.append(reinterpret_cast<char const *>(&elem),
                        sizeof(size_type));
    }
    return binary;
}

std::set<InvIndex::size_type> InvIndex::deserializeSet(std::string binary) {
    std::set<size_type> s;
    if (binary.size() % sizeof(size_type) != 0) {
        throw std::runtime_error("Binary data size is not aligned with size_type");
    }
    size_type cnt = binary.size() / sizeof(size_type);
    for (size_type i = 0; i < cnt; ++i) {
        size_type num;
        std::memcpy(&num, binary.data() + i * sizeof(size_type),
                    sizeof(size_type));
        s.insert(num);
    }
    return s;
}

void InvIndex::eraseAll() {
    std::string password;  
    std::puts("请输入密码: ");
    std::getline(std::cin, password);
    if (password != erase_password) {
        std::puts("密码错误，请检查是否用错了函数");
    }

    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());    
    std::vector<std::string> keys;

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        keys.push_back(it->key().ToString());
    }
    delete it;

    leveldb::WriteBatch batch;
    for (auto const& key : keys) {
        batch.Delete(key);
    }
    leveldb::Status status = db->Write(leveldb::WriteOptions(), &batch);
    checkStatus(status, std::string(" "));
    size = 0;
}

// 查看前 n 条内容
void InvIndex::displayNth(size_type n) {
    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
    size_type cnt {0};
    std::string ids;
    for (it->SeekToFirst(); it->Valid() and cnt < n; it->Next()) {
        fmt::print("Key: {}\nValues: ", it->key().ToString());
        auto ids = deserializeSet(it->value().ToString());
        for (auto const id : ids) {
            fmt::print("{} ", id);
        } 
        fmt::print("\n");
        cnt += 1;
    } 
    delete it;
}