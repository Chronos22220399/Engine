#pragma once
#include "includes.h"
#include "egutils.h"
#include <iostream>
#include <list>
#include <type_traits>
#include <unordered_map>


template <typename Key, typename Value>
struct Node {
	static_assert(has_hash_v<Key>);

	explicit Node() = default;

	explicit Node(Key const &key, Value const &value)
		: key(key),
		  value(value) {}

	explicit Node(Key &&key, Value &&value)
		: key(std::move(key)),
		  value(std::move(value)) {}

	~Node() = default;

	Key key;
	Value value;
};

template <typename Key = int, typename Value = int,
		  typename Container = std::list<Node<Key, Value>>>
class Cache {
	static_assert(is_iterable_v<Container> and has_hash_v<Key>);

public:
	using containerIterator = typename Container::iterator;
	using node_type = Node<Key, Value>;

	Cache(size_t const &capacity) : capacity(capacity) {}

	// 将信息存入缓存
	virtual void put(Key const &key, Value const &value) = 0;

	// 获取信息
	virtual std::optional<Value> get(Key const &key) = 0;

protected:
	// 获取信息时未能找到信息
	virtual std::optional<Value> doNotFoundKeyWhenGetting(Key const &key) = 0;

	// 获取信息时找到了信息返回时
	virtual std::optional<Value> foundKeyWhenGetting(Key const &key,
													 Value const &value) = 0;

	std::unordered_map<Key, containerIterator> keyToIterator;
	Container cache;
	size_t capacity;
};

template <typename Key = int, typename Value = int,
		  typename Container = std::list<Node<Key, Value>>>
class LRUCache : public Cache<Key, Value, Container> {
	static_assert(has_hash_v<Key>, "请检查键的类型，保证其可哈希");
	static_assert(is_iterable_v<Container>,
				  "请使用可迭代对象作为缓存容器（最好是list、vector）");
	static_assert(has_splice_v<Container>, "当前版本仅支持 list\n");

	using containerIterator = typename Container::iterator;
	using node_type = Node<Key, Value>;

public:
	LRUCache(size_t const &capacity = 1000)
		: Cache<Key, Value, Container>(capacity) {}

	void put(Key const &key, Value const &value) override {
		// 若使用的是 list
		auto &keyToIterator = this->keyToIterator;
		auto &cache = this->cache;
		// 找到了元素则将其更新
		if (auto const &it = keyToIterator.find(key);
			it != keyToIterator.end()) {
			containerIterator const &listIt = it->second;
			cache.splice(cache.begin(), cache, listIt);
			listIt->value = value;
		}
		// 容量抵达上限, 删除尾部元素
		if (cache.size() == this->capacity) {
			node_type const &listIt = cache.back();
			keyToIterator.erase(listIt.key);
			cache.pop_back();
		}
		cache.emplace_front(key, value);
		keyToIterator[key] = cache.begin();
	}

	// get 及 doNotFoundKeyWhenGetting 用于实现模版模式，以便于用户自定义操作
	std::optional<Value> get(Key const &key) override {
		// 暂时只支持 list
		auto const &keyToIterator = this->keyToIterator;
		auto &cache = this->cache;
		auto const &it = keyToIterator.find(key);
		// 未能找到元素
		if (it == keyToIterator.end()) {
			return doNotFoundKeyWhenGetting(key);
		}
		Value const &retValue = it->second->value;
		cache.splice(cache.begin(), cache, it->second);
		return foundKeyWhenGetting(key, retValue);
	}

	virtual std::optional<Value>
	doNotFoundKeyWhenGetting(Key const &key) override {
		std::cout << "未能找到元素" << std::endl;
		return std::nullopt;
	}

	virtual std::optional<Value>
	foundKeyWhenGetting(Key const &key, Value const &value) override {
		return {value};
	}
};

template <typename Key, typename Value, typename Container = std::list<Node<Key, Value>>>
using ListLRUCache = LRUCache<Key, Value, Container>;