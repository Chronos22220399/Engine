#include "Cutter.h"

static Cutter cutter{};
static std::vector<std::string> words;

void test(std::string const &text) {
	auto start = std::chrono::high_resolution_clock::now();
	cutter.advancedDivorce(text, words);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	// std::cout << limonp::Join(words.begin(), words.end(), " ") << std::endl;
	std::cout << "耗时: " << duration.count() << std::endl;
}