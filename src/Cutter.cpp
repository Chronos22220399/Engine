#include "Cutter.h"


Egutils::StringProcessor::StringProcessor(): jieba(
        "../cppjieba/dict/jieba.dict.utf8", 
        "../cppjieba/dict/hmm_model.utf8", 
        "../cppjieba/dict/user.dict.utf8", 
        "../cppjieba/dict/idf.utf8",
        "../cppjieba/dict/stop_words.utf8"
    ) {}

std::set<std::string> Egutils::StringProcessor::get_intersection(std::string const& left, std::string const& right) {
    std::function<std::set<std::string>(std::string const& str)> from_string_to_set = [this](std::string const& str) {
        std::vector<std::string> vec;
        this->jieba.CutForSearch(str, vec);
        return std::set<std::string>(std::make_move_iterator(vec.begin()), std::make_move_iterator(vec.end())); 
    };

    auto set_left = from_string_to_set(left);
    auto set_right = from_string_to_set(right);
    std::set<std::string> result;
    std::set_intersection(
        set_left.begin(), set_left.end(),
        set_right.begin(), set_right.end(),
        // std::back_inserter(result)
        std::inserter(result, result.begin())
    );
    return result;
}

std::string Egutils::StringProcessor::strip(std::string const& str) {
    auto start = str.find_first_not_of(" \n\t\r");
    if (start == std::string::npos) {
        return "";
    }
    auto end = str.find_last_not_of(" \n\t\r");
    return str.substr(start, end-start+1);
}

std::string Egutils::StringProcessor::process(std::string const& text) {
    return strip(text);
}

    // & > |
    // "nihoa" | "helo" & "and" | "hllo" |"hello" &
std::string Egutils::StringProcessor::advancedProcess(std::string const& text) {
    using namespace std;
    // preprocess
    stack<string> stk;
    size_t begin = 0;
    size_t end = text.find_first_of("|&", begin);
    bool end_with_op = false;
    string str {};
    while (end != string::npos) {
        str = text.substr(begin, end-begin);
        stk.push(strip(str));
        auto op = text.substr(end, 1);
        if (op == "|") {
            if (end == text.length()-1) {
                end_with_op = true;
            }
            // do nothing
        } else if (op == "&") {
            if (end == text.length()-1) {
                // eliminate the top element, because everything & zero equals zero
                stk.pop();
                end_with_op = true;
                break;
            }
            auto left = stk.top();
            stk.pop();
            begin = end + 1;
            end = text.find_first_of("|&", begin);
            auto right = strip(text.substr(begin, end-begin));
            auto res = get_intersection(left, right);
            std::string temp_str {};
            for (auto& elem : res) {
                temp_str += elem + " ";
            }
            stk.push(strip(temp_str));
        } else {
            throw runtime_error("未知高级运算符");
        }
        begin = end + 1;
        end = text.find_first_of("|&", begin);
    }
    if (not end_with_op) {
        stk.push(strip(text.substr(begin, -1)));
    }
    std::string wordlist {};
    while (not stk.empty()) {
        wordlist += stk.top() + " ";
        stk.pop();
    }
    return wordlist;
}


Cutter::Cutter(): jieba(
        "../cppjieba/dict/jieba.dict.utf8", 
        "../cppjieba/dict/hmm_model.utf8", 
        "../cppjieba/dict/user.dict.utf8", 
        "../cppjieba/dict/idf.utf8",
        "../cppjieba/dict/stop_words.utf8"
        ) {}

void Cutter::normalDivorce(std::string const& text, std::vector<std::string> &words) {
    jieba.CutForSearch(text, words, true);
}

void Cutter::advancedDivorce(std::string const& text, std::vector<std::string> &words) {
    std::string sentence = text_processor.advancedProcess(text);
    jieba.CutForSearch(sentence, words);
}



// just for fun
template<typename T>
using has_value_type = std::void_t<typename T::value_type>;

template<typename T, typename = void>
struct HasValueType: std::false_type {};

template<typename T>
struct HasValueType<T, has_value_type<T>>: std::true_type {};

struct WithVT { using value_type = int; };
struct WithoutVT { };
