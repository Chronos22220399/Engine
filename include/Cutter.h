#pragma once
#include "includes.h"
#include "cppjieba/Jieba.hpp"


template <typename T>
auto display(T const& t) {
    for (auto &elem : t) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


namespace Egutils {

struct StringProcessor {
public:
    StringProcessor();

    std::set<std::string> get_intersection(std::string const& left, std::string const& right);

    std::string strip(std::string const& str);

    std::string process(std::string const& text);

    std::string advancedProcess(std::string const& text);

private:
    const cppjieba::Jieba jieba;
};
}

class Cutter {
public:
    Cutter();

    void normalDivorce(std::string const& text, std::vector<std::string> &words);

    void advancedDivorce(std::string const& text, std::vector<std::string> &words);

private:
    cppjieba::Jieba jieba;
    Egutils::StringProcessor text_processor;
};