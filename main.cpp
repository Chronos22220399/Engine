#include <iostream>
#include <list>
#include <type_traits>
#include <unordered_map>

template <typename T, template <typename> class Checker>
struct UniChecker {
    template <typename U>
    static auto test(int) -> decltype(Checker<U>::check(std::declval<U>()),
                                      std::true_type{});
    template <typename>
    static std::false_type test(...);

    static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T, template <typename> class Checker>
inline constexpr bool unicheck_v = UniChecker<T, Checker>::value;

template <typename T>
struct has_hash {
    static auto check(T) -> decltype(std::hash<T>{}(std::declval<T>()));
};

template <typename T, typename = void>
struct has_find : std::false_type {};

template <typename T>
struct has_find<T, std::void_t<decltype(std::declval<T>().find(std::declval<typename T::key_type>()))>> : std::true_type {};

/* // 辅助变量模板（C++17 起） */
/* template <typename T> */
/* inline constexpr bool has_find_v = has_find<T>::value; */
/* template <typename Container> */
/* struct has_find_checker { */
/*     // 针对 std::map, std::unordered_map 等具有 find 成员函数的容器 */
/*     template <typename U> */
/*     static auto check(U) -> decltype(std::declval<U>().find( */
/*                                          std::declval<typename U::key_type>()), */
/*                                      std::true_type{}); */
/*  */
/*     // 如果没有 find 成员函数，则返回 false_type */
/*     template <typename> */
/*     static std::false_type check(...); */
/*     static constexpr bool value = decltype(check<Container>(0))::value; */
/* }; */

template <typename Container>
struct is_iterable {
    static auto
        check(Container) -> decltype(std::begin(std::declval<Container>()),
                                     std::end(std::declval<Container>()));
};

template <typename T>
inline constexpr bool has_hash_v = unicheck_v<T, has_hash>;

template <typename Container>
inline constexpr bool has_find_v = has_find<Container>::value;

template <typename Container>
inline constexpr bool is_iterable_v =
    unicheck_v<Container, is_iterable>;

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


int main() {
    /* Cache<int, int> cache; */
    static_assert(is_iterable_v<std::list<int>>);
    std::list<int> li;
    std::cout << has_find_v<std::list<int>> << std::endl;
    return 0;
}

template <typename Key = int, typename Value = int,
          typename Container = std::list<Node<Key, Value>>>
class Cache {
    static_assert(is_iterable_v<Container> and has_find_v<Container>);

public:
    using containerIterator = typename Container::iterator;

private:
    std::unordered_map<Key, containerIterator> keyToIterator;
    Container cache;
};
