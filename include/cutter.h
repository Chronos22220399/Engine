#pragma once
#include "includes.h"
#include "cppjieba/Jieba.hpp"
#include "egutils.h"


class Cutter {
public:
    Cutter();

    std::set<std::string> normalDivorce(std::string const& text);

    std::set<std::string> advancedDivorce(std::string const& text);


private:
    cppjieba::Jieba jieba;
    TextProcessor text_processor;
    CharUtils char_utils;
};
