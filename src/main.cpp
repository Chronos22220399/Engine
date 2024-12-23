#include "cutter.h"
#include "includes.h"
#include "InvIndex.h"

struct Node {
    int key;
    int value;
};

class Cache {};

class LRUCache {
public:
    LRUCache(size_t const &capacity) : capacity(capacity) {}

    int doWhenNotFound() {
        return -1;
    };

    int doWhenFound(int value) {
        return value;
    }

    int get(int key) {
        auto const it = keyToIterator.find(key);
        if (it == keyToIterator.cend()) {
            return doWhenNotFound();
        }
        auto const &listIt = it->second;
        cache.splice(cache.begin(), cache, listIt);
        return doWhenFound(listIt->value);
    }

    void put(int key, int value) {
        if (auto const it = keyToIterator.find(key);
            it != keyToIterator.cend()) {
            auto const &listIt = it->second;
            cache.splice(cache.begin(), cache, listIt);
            listIt->value = value;
        }
        if (cache.size() == capacity) {
            Node const &lastNode = cache.back();
            keyToIterator.erase(lastNode.key);
            cache.pop_back();
        }
        cache.emplace_back(key, value);
        keyToIterator[key] = cache.begin();
    }

private:
    size_t const capacity;
    std::list<Node> cache;
    std::unordered_map<int, std::list<Node>::iterator> keyToIterator;
};

int main() {
    LRUCache lru {10};
    lru.put(10, 20);
    std::cout << lru.get(10) << std::endl;
    std::cout << lru.get(1) << std::endl;
    return 0;
}
