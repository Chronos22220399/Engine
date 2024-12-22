#pragma once
#include "includes.h"
#include <fmt/format.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>


struct DocWordsWithId {
private:
    using size_type = uint32_t;
public:
    DocWordsWithId() = default;
    DocWordsWithId(std::vector<std::string> const&words, size_type id): doc_words(words), id(id) {}
    std::vector<std::string> doc_words;
    size_type id;
};

class InvIndex {
	using size_type = uint32_t;
public:


	~InvIndex(); 

    // 将一篇文档中的词语批量存入倒排索引
	std::optional<size_type> putBatch(DocWordsWithId const &doc);
	
	// 将单个词语存入倒排索引
	std::optional<size_type>
	putSingle(std::pair<std::string, size_type> const &single_word);

	// 通过单个词语获取文档列表
	std::optional<std::set<size_type>> getSingle(std::string const &word); 

	// 通过词语获取一系列文档列表, 由于是通过 words 中的 word 获取，因此不使用迭代器
	std::optional<std::map<std::string, std::set<size_type>>> getByWords(std::set<std::string> const& words);

	// 获取前 n 个索引
	std::optional<std::map<std::string, std::set<size_type>>> getInvIndexNCnt(size_type const& count);

	InvIndex(InvIndex const&) = delete;

	InvIndex& operator=(InvIndex const&) = delete;
private:
	InvIndex(std::string const &db_name = "Inv",
			 bool const &create_if_missing = true);

	std::string serializeSet(std::set<size_type> const &vec);

	std::set<size_type> deserializeSet(std::string binary);
    
	template <typename T>
	std::optional<T> checkStatus(leveldb::Status &status, T const &result) {
		if (status.IsNotFound()) {
			fmt::println("未能找到: {}", status.ToString(), __FILE__);
			return std::nullopt; 
		} else if (!status.ok()) {
			fmt::println("{}", status.ToString(), __FILE__);
			return std::nullopt; 
		}
		return {result};
	}

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
		std::optional<size_type> insert(DocWordsWithId const& doc);
		// Get doc id set by single word when running
		std::optional<std::set<size_type>> get(std::string const& word);
		// Get doc id lists by words list when running
		std::optional<std::set<size_type>> getWords(std::set<std::string> words);
        // Display to debug
        void display() {
            for (auto const& key : cache) {
                std::cout << key.first << " : " << key.second << std::endl;
            }
        }
        // Get the instance of cache
        inline static InvCache& getCache() {
            static InvCache instance {};
            return instance;
        }


		InvCache(InvCache const&) = delete;
		InvCache& operator=(InvCache const&) = delete;
	private:
		InvCache() = default;
		size_t capacity;
		size_t size;
    };

public:
	inline static InvIndex& getInv() {
		static InvIndex instance {};
		return instance;
	}

    inline static InvCache& getCache() {
        return InvCache::getCache();
    }

	leveldb::DB *db = nullptr;
	std::string const ROOT_PATH =
		"/Users/wuming/Desktop/Engine/Datas/";
};
