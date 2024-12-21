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


class Cutter {
public:
    Cutter();

    std::set<std::string> normalDivorce(std::string const& text);

    std::set<std::string> advancedDivorce(std::string const& text);


private:
    cppjieba::Jieba jieba;
    Egutils::TextProcessor text_processor;
    Egutils::CharUtils char_utils;
};
