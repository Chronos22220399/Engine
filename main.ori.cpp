/* #include <iostream> */
/* #include <list> */
/* #include <type_traits> */
/* #include <unordered_map> */
/*  */
/* template <typename T> */
/* struct has_hash { */
/* private: */
/*     template <typename U> */
/*     static auto test(int) -> decltype(std::hash<U>{}(std::declval<U>()), */
/*                                       std::true_type{}); */
/*  */
/*     template <typename> */
/*     static std::false_type test(...); */
/*  */
/* public: */
/*     static constexpr bool value = decltype(test<T>(0))::value; */
/* }; */
/*  */
/* template <typename Container> */
/* struct is_iterable { */
/* private: */
/*     template <typename U> */
/*     static auto test(int) -> decltype(std::begin(std::declval<U>()), */
/*                                       std::end(std::declval<U>()), */
/*                                       std::true_type()); */
/*     static std::false_type test(...); */
/*  */
/* public: */
/*     static constexpr bool value = decltype(test<Container>(0))::value; */
/* }; */
/*  */
/* template <typename Container> */
/* struct has_find { */
/* private: */
/*     template <typename U> */
/*     static auto test(int) -> decltype(std::find(std::declval<U>()), */
/*                                       std::true_type{}); */
/*  */
/*     template <typename> */
/*     static std::false_type test(...); */
/*  */
/* public: */
/*     static constexpr bool value = decltype(test<Container>(0))::value; */
/* }; */
/*  */
/* template <typename T> */
/* inline constexpr bool has_hash_v = has_hash<T>::value; */
/*  */
/* template <typename Container> */
/* inline constexpr bool is_iterable_v = is_iterable<Container>::value; */
/*  */
/* template <typename Container> */
/* inline constexpr bool has_find_v = has_find<Container>::value; */
/*  */
/* template <typename Key, typename Value> */
/* struct Node { */
/*     static_assert(has_hash_v<Key>); */
/*  */
/*     explicit Node() = default; */
/*  */
/*     explicit Node(Key const &key, Value const &value) */
/*         : key(key), */
/*           value(value) {} */
/*  */
/*     explicit Node(Key &&key, Value &&value) */
/*         : key(std::move(key)), */
/*           value(std::move(value)) {} */
/*  */
/*     ~Node() = default; */
/*  */
/*     Key key; */
/*     Value value; */
/* }; */
/*  */
/* template <typename Key = int, typename Value = int, */
/*           typename Container = std::list<Node<Key, Value>>> */
/* class Cache { */
/* public: */
/*     using containerIterator = typename Container::iterator; */
/*  */
/* private: */
/*     std::unordered_map<Key, containerIterator> keyToIterator; */
/*     Container cache; */
/* }; */
/*  */
/* int main() { */
/*     /* Cache cache; */ */
/*     std::cout << is_iterable_v<std::list<Node<int, int>>> << std::endl; */
/*     return 0; */
/* } */
