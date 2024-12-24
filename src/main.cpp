#include "cutter.h"
#include "egutils.h"
#include "includes.h"
#include "inv_index.h"

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

	// 将信息存入缓存
	virtual void put(Key const &key, Value const &value) = 0;

	// 获取信息
	// virtual std::optional<Value> get(Key const &key) = 0;

protected:
	// 获取信息时未能找到信息
	// virtual std::optional<Value> doNotFoundKeyWhenGetting(Key const &key) =
	// 0;

	// 获取信息时找到了信息返回时
	// virtual std::optional<Value> foundKeyWhenGetting(Key const &key) = 0;

private:
	std::unordered_map<Key, containerIterator> keyToIterator;
	Container cache;
};

template <typename Key = int, typename Value = int,
		  typename Container = std::list<Node<Key, Value>>>
class LRUCache : public Cache<Key, Value, Container> {
	static_assert(is_iterable_v<Container> and has_hash_v<Key>);

public:
	void put(Key const &key, Value const &value) {
		// 若使用的是 list
		if constexpr (has_splice_v<std::decay_t<Container>>) {
			std::cout << "hello\n";
		}
		// 暂时只支持 list
		static_assert(has_splice_v<std::decay_t<Container>>, "当前版本仅支持 list\n");
	}
};

int main() {
	LRUCache<int, int, std::list<Node<int, int>>> lru;
	lru.put(1, 1);
	return 0;
}
