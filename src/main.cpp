#include "Cutter.h"
#include "includes.h"
#include <leveldb/db.h>

template <typename ...ARGS>
void print(ARGS const& ...args) {
	((std::cout << args) << ... ) << std::endl;
}

const std::string ROOT_PATH = "/Users/wuming/Desktop/Engine/Datas/Inv_index/";
void test() {
	leveldb::DB *db = nullptr;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, ROOT_PATH + std::string("inv"), &db);

	std::cout << "db started, status: " << status.ToString() << std::endl;
	assert(status.ok());
	delete db;
}

int main() {
	print(__FILE__);
	test();
	return 0;
}