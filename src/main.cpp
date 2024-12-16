#include "Cutter.h"

int main() {
    Cutter cutter {};
    std::string text { "你好 | 再见 & 再见吧 | 华为 | 小米|" };
    std::vector<std::string> words;
    cutter.advancedDivorce(text, words);

    std::cout << limonp::Join(words.begin(), words.end(), " ") << std::endl;
    return 0;
}