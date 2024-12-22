#include "inv_index.h"


/*
倒排索引开始
*/
InvIndex::InvIndex(std::string const &db_name,
            bool const &create_if_missing) {
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
    auto doc_id = doc.id;
    for (auto const &word: doc.doc_words) {
        std::string ids;
        auto status = db->Get(leveldb::ReadOptions(), word, &ids);
        if (!status.ok()) {
            LOG();
            fmt::print("获取键值对失失败{}\n", status.ToString());
            return std::nullopt;
        }	
        std::set<size_type> vec_id = deserializeSet(ids);
        vec_id.insert(doc_id);
        ids = serializeSet(vec_id);
        batch.Put(word, ids);
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

/*
倒排索引结束
*/

/*
倒排索引缓存开始
*/
// 设置缓存容量
// 返回正数，说明容量减小，负数说明容量增大
std::optional<InvIndex::size_type> InvIndex::InvCache::resize(size_type capacity) {
    this->capacity = capacity;
    size_type ori_size = size;
    auto& cache = getCache().cache;
    // 默认删除尾部元素
    while(size >= capacity) {
        auto it = cache.end();
        cache.erase(--it);
    }
    return { ori_size - capacity + 1 };
}

// Initialize the cache, return the inserted elem count
std::optional<InvIndex::size_type> InvIndex::InvCache::initialize(size_type capacity = 10000) {
    this->capacity = capacity;
    this->size = 0;
    // insert data from InvIndex
    auto& inv = InvIndex::getInv();
    auto result = inv.getInvIndexNCnt(capacity);
    if (!(result and result.has_value())) {
        LOG();
        return std::nullopt; 
    }
    this->size = result.value().size();
    this->cache.insert(std::move_iterator(result.value().begin()), std::move_iterator(result.value().end()));
    return { size };
}

// Insert value when running(runtime)
std::optional<InvIndex::size_type> InvIndex::InvCache::insert(DocWordsWithId const& doc) {
    size_type doc_id = doc.id;
    for (auto const& word : doc.doc_words) {
        auto result = cache[word].insert(doc_id);
        if (not result.second) {
            LOG();
            return std::nullopt;
        }
    }
    return { doc.doc_words.size() };
}

// Get doc id set by single word when running
// firstly search the cache
// secondly search the InvIndex
std::optional<std::set<InvIndex::size_type>> InvIndex::InvCache::get(std::string const& word) {
    // firstly search the cache
    auto it = cache.find(word);
    // find out
    if (it == cache.end()) {
        auto result = getInv().getSingle(word);
        if (!result) {
            return std::nullopt;
        }
        // 在倒排索引中找到了
        // 将单词添加到缓存中
        if (size >= capacity) {
            LOG();
            auto result = resize(capacity/10);
            size = result.value();
            fmt::print("缓存容量到达上限，现已删除 {} 条缓存", size);
        }
        cache[word] = result.value();
        size++;
        return { result.value() };
    }
    return { it->second };
}

// Get doc id lists by words list when running
std::optional<std::set<InvIndex::size_type>> InvIndex::InvCache::getWords(std::set<std::string> words) {
    std::set<size_type> retSet;
    for (auto const& word : words) {
        auto result = get(word);
        if (result.has_value()) {
            retSet.insert(std::move_iterator(result.value().begin()), std::move_iterator(result.value().end()));            
        }
    }
    if (retSet.empty()) {
        return std::nullopt;
    }
        return { retSet };
    }
/*
倒排索引缓存结束
*/
