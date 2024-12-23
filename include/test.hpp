#include "Cutter.h"
#include "includes.h"

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

void test_1() {
	std::string text {R"(分配设备：用户输入作业名、设备类名和相对号。系统检查设备类表，若有空闲设备，则从设备表中选择符合条件的设备并分配给作业，更新设备类表和设备表中的状态。
	•	回收设备：用户输入作业名和设备类名，系统查找设备表中的作业名，释放设备并更新状态，设备类表中的“现存好的设备”数增加。)"};
	Cutter cutter {};
	// std::vector<std::string> words;
	auto words = cutter.advancedDivorce(text);
	std::cout << words << std::endl;	
}
