#pragma once
#include "includes.h"
#include "cppjieba"

namespace Egutils {

/*
 打印容器内容
*/
template <typename T>
auto display(T const& t) {
    for (auto &elem : t) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}


struct TextProcessor {
public:
    TextProcessor();

    std::set<std::string> getIntersection(std::string const& left, std::string const& right) const;

    std::string strip(std::string const& str) const;

    std::string process(std::string const& text) const;

    std::string advancedProcess(std::string const& text) const;

    std::string setToString(std::set<std::string> const& s) const;

private:
    const cppjieba::Jieba jieba;
};

struct CharUtils {
    void extractChar(std::set<std::string> &s, std::wstring const &charSet);
    
};

}
