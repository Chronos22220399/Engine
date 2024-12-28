#include "cache.hpp"
#include "cutter.h"
#include "egutils.h"
#include "includes.h"
#include "inv_index.h"
#include "test.hpp"
#include "test_threadpool.hpp"
#include "thread_pool.hpp"
#include "Search.hpp"
#include "NewsOperate.hpp"


void RunServer() {
	Cutter cutter;
	InvIndex inv;
	InvLRUCache invCache(inv);
	std::string server_address {"0.0.0.0:11111"};
	Search search(cutter, invCache);
	NewsOperator newsOperator(cutter, inv);
	grpc::ServerBuilder builder;

	builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
	builder.RegisterService(&search);
	builder.RegisterService(&newsOperator);

	std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
	fmt::print("开始监听 {}\n", server_address);
	server->Wait();
}



int main() {
	changeWorkSpace();
	// test_inv_index();
	RunServer();
	// InvIndex inv;
	// inv.eraseAll();
	// inv.displayNth();
	// Cutter cutter;
	// test_inv_index();
	
	// std::optional<int> a = std::nullopt;
	// std::cout << a.has_value() << std::endl;
	// test_cache();
	// test_threadpool(cutter);
	
	// InvLRUCache lru;
	// lru.put("heelo", {1});
	// auto value = lru.get("heelo");
	// if (value.has_value()) {
	// 	for (auto &v: value.value()) {
	// 		std::cout << v << std::endl;
	// 	}
	// }
	return 0;
}
