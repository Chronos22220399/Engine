#include "cache.hpp"
#include "cutter.h"
#include "egutils.h"
#include "includes.h"
#include "inv_index.h"
#include "test_threadpool.hpp"
#include "thread_pool.hpp"

template <typename Key, typename Value,
		  typename Container = std::list<Node<Key, Value>>>
using ListLRUCache = LRUCache<Key, Value, Container>;

using size_type = uint32_t;
using InvNode = Node<std::string, std::set<size_type>>;

// MARK: 还需要完成上锁相关的内容，具体在 cache.hpp 中
class InvLRUCache : public ListLRUCache<std::string, std::set<size_type>,
										std::list<InvNode>> {
public:
	auto doNotFoundKey(std::string const &key)
		-> std::optional<std::set<size_type>> override {
		auto result = inv->getSingle(key);
		if (result.has_value()) {
			this->put(key, result.value());
			return result;
		}
		return std::nullopt;
	}

private:
	std::shared_ptr<InvIndex> inv;
};

int main() {
	InvLRUCache lru;
	lru.put("heelo", {1});
	auto value = lru.get("heelo");
	if (value.has_value()) {
		for (auto &v: value.value()) {
			std::cout << v << std::endl;
		}
	}
	// changeWorkSpace();
	// Cutter cutter;
	// test_threadpool(cutter);
	return 0;
}
