#pragma once
#include "includes.h"

class ThreadPool {
public:
	explicit ThreadPool(size_t const& capacity);

	ThreadPool(ThreadPool const&) = delete;

	~ThreadPool();

	template <typename F, typename ...Args>
	auto enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type>;

private:
	std::vector<std::thread> workers;
	std::queue<std::function<void()>> tasks;
	std::condition_variable condition;
	std::mutex queueMutex;
	bool stop;
	size_t capacity;
};

inline ThreadPool::ThreadPool(size_t const& capacity): stop(false), capacity(capacity) {
	for (size_t i = 0; i < capacity; ++i) {
		workers.emplace_back([this](){
			while (true) {
				std::function<void()> task;
				{
					std::unique_lock lock { queueMutex };
					// 收到结束信号或还有任务就接触阻塞
					condition.wait(lock, [this](){
						return stop || !tasks.empty();
					});

					// 只要受到结束信号且队列中没有任务了就返回，否则就执行任务
					if (stop && tasks.empty()) {
						return;
					}
					task = tasks.front();
					tasks.pop();
				}
				task();
			}
		});
	}
}

inline ThreadPool::~ThreadPool() {
	{
		std::lock_guard lock { queueMutex };
		stop = true;
	}
	condition.notify_all();
	for (auto &worker : workers) {
		worker.join();
	}
}

template <typename F, typename ...Args>
auto ThreadPool::enqueue(F &&f, Args &&...args) -> std::future<typename std::result_of<F(Args...)>::type> {
	using returnType = typename std::result_of<F(Args...)>::type;
	auto task = std::make_shared<std::packaged_task<returnType()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);

	std::future<returnType> ret = task->get_future();
	{
		std::lock_guard lock { queueMutex };
		if (stop) {
			throw std::runtime_error("错误：人物入队时销毁了线程池");
		}
		tasks.emplace([task](){
			(*task)();	
		});
	}
	condition.notify_one();
	return ret;
}
