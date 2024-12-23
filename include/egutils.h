#pragma once
#include "cppjieba"
#include "includes.h"

namespace Egutils {

/*
 打印容器内容
*/
template <typename T>
auto display(T const &t) {
    for (auto &elem: t) {
        std::cout << elem << " ";
    }
    /* std::cout << "\n"; */
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
    void extractChar(std::set<std::string> &s, std::wstring const &charSet);

    std::string wideToUtf8(wchar_t wideChar);
};

} // namespace Egutils
