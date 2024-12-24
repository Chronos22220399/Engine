#include "cutter.h"
#include "fmt/format.h"
#include "includes.h"
#include <codecvt>
#include <locale>


Cutter::Cutter()
	: jieba("../cppjieba/dict/jieba.dict.utf8",
			"../cppjieba/dict/hmm_model.utf8",
			"../cppjieba/dict/user.dict.utf8", "../cppjieba/dict/idf.utf8",
			"../cppjieba/dict/stop_words.utf8") {}

std::set<std::string> Cutter::normalDivorce(std::string const &text) {
	std::vector<std::string> words;
	std::set<std::string> result{};
	jieba.CutForSearch(text, words, true);
	result.insert(std::move_iterator(words.begin()),
				  std::move_iterator(words.end()));
	char_utils.extractChar(result);
	return result;
}

std::set<std::string> Cutter::advancedDivorce(std::string const &text) {
	std::vector<std::string> words;
	std::set<std::string> result{};
	std::string sentence = text_processor.advancedProcess(text);
	jieba.CutForSearch(sentence, words);
	result.insert(std::move_iterator(words.begin()),
				  std::move_iterator(words.end()));
	char_utils.extractChar(result);
	return result;
}


template <typename T>
using has_value_type = std::void_t<typename T::value_type>;

template <typename T, typename = void>
struct HasValueType : std::false_type {};

template <typename T>
struct HasValueType<T, has_value_type<T>> : std::true_type {};

struct WithVT {
	using value_type = int;
};

struct WithoutVT {};
