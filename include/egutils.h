#pragma once
#include "cppjieba/Jieba.hpp"
#include "includes.h"

/*
矫验
*/
template <typename T, typename = void>
struct has_hash : std::false_type {};

template <typename T>
struct has_hash<T, std::void_t<decltype(std::hash<T>{}(std::declval<T>()))>>
	: std::true_type {};

template <typename Container, typename = void>
struct has_find : std::false_type {};

template <typename Container>
struct has_find<Container, std::void_t<decltype(std::declval<Container>().find(
							   std::declval<typename Container::key_type>()))>>
	: std::true_type {};

template <typename Container, typename = void>
struct is_iterable : std::false_type {};

template <typename Container>
struct is_iterable<Container,
				   std::void_t<decltype(std::begin(std::declval<Container>()),
										std::end(std::declval<Container>()))>>
	: std::true_type {};

template <typename Container, typename = void>
struct has_splice: std::false_type {};

template <typename Container>
struct has_splice<Container, std::void_t<decltype(std::declval<Container>().splice(std::declval<typename Container::iterator>(), std::declval<Container>(), std::declval<typename Container::iterator>()))>>: std::true_type {};

template <typename T>
inline constexpr bool has_hash_v = has_hash<T>::value;

template <typename Container>
inline constexpr bool has_find_v = has_find<Container>::value;

template <typename Container>
inline constexpr bool is_iterable_v = is_iterable<Container>::value;

template <typename Container>
inline constexpr bool has_splice_v = has_splice<Container>::value;
/*
矫验
*/

/*
 打印容器内容
*/
template <typename T>
auto display(T const &t) {
	for (auto &elem: t) {
		std::cout << elem << " ";
	}
	std::cout << "\n";
}

struct TextProcessor {
public:
	TextProcessor();

	std::set<std::string> getIntersection(std::string const &left,
										  std::string const &right) const;

	std::string strip(std::string const &str) const;

	std::string process(std::string const &text) const;

	std::string advancedProcess(std::string const &text) const;

	std::string setToString(std::set<std::string> const &s) const;

private:
	cppjieba::Jieba const jieba;
};

struct CharUtils {
	void extractChar(std::set<std::string> &s,
					 std::wstring const &charSet =
						 L" ,,.\"\'`~!/\\<•>-=()_@#$%^*。，《》（）-——；：'"
						 "{}「」,“”【】～·！？、，");

	std::string wideToUtf8(wchar_t wideChar);
};

/*
 打印容器内容
*/

/***********************************************/
// 已废弃
namespace old {

template <typename T, template <typename> class Checker>
struct UniChecker {
	template <typename U>
	static auto test(int)
		-> decltype(Checker<U>::check(std::declval<U>()), std::true_type{});
	template <typename>
	static std::false_type test(...);

	static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_hash {
	static auto check(T) -> decltype(std::hash<T>{}(std::declval<T>()));
};

template <typename Container>
struct has_find {
	static auto check(Container) -> decltype(std::declval<Container>().find(
		std::declval<typename Container::key_type>()));
};

template <typename Container>
struct is_iterable {
	static auto check(Container)
		-> decltype(std::begin(std::declval<Container>()),
					std::end(std::declval<Container>()));
};

template <typename T, template <typename> class Checker>
inline constexpr bool unicheck_v = UniChecker<T, Checker>::value;

template <typename T>
inline constexpr bool has_hash_v = unicheck_v<T, has_hash>;

template <typename Container>
inline constexpr bool has_find_v = unicheck_v<Container, has_find>;

template <typename Container>
inline constexpr bool is_iterable_v = unicheck_v<Container, is_iterable>;

} // namespace old
