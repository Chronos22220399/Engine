#pragma once
#include "includes.h"

namespace old {
/*
    倒排索引的缓存
*/
struct InvCache {
    std::map<std::string, std::set<size_type>> cache;
    // Set capacity of lines
    std::optional<size_type> resize(size_type capacity);
    // Initialize the cache, return the inserted elem count
    std::optional<size_type> initialize(size_type capacity);
    // Insert value when running(runtime)
    std::optional<size_type> insert(DocWordsWithId const &doc);
    // Get doc id set by single word when running
    std::optional<std::set<size_type>> get(std::string const &word);
    // Get doc id lists by words list when running
    std::optional<std::set<size_type>>
    getWords(std::set<std::string> words);

    // Display to debug
    void display() {
        for (auto const &key: cache) {
            std::cout << key.first << " : ";
            for (auto const &elem: key.second) {
                std::cout << elem << std::endl;
            }
        }
    }

    // Get the instance of cache
    static inline InvCache &getCache() {
        static InvCache instance{};
        return instance;
    }

    InvCache(InvCache const &) = delete;
    InvCache &operator=(InvCache const &) = delete;

private:
    InvCache() = default;
    size_t capacity;
    size_t size;
};

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
}