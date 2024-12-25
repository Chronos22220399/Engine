#include "cutter.h"
#include "egutils.h"
#include "includes.h"
#include "inv_index.h"
#include "cache.hpp"
#include "thread_pool.hpp"
#include "test_threadpool.hpp"

int main() {
	changeWorkSpace();
	Cutter cutter;
	test_threadpool(cutter);
	// std::cout
	// 	<< has_splice_v<std::decay_t<std::list<Node<int, int>>>> << std::endl;
	// LRUCache<int, int, std::list<Node<int, int>>> lru;
	// lru.put(1, 1);
	// auto value = lru.get(2);
	// if (value.has_value()) {
	// 	std::cout << value.value() << std::endl;
	// }
	return 0;
}
