#pragma once
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <mutex>

using namespace std;

class ThreadPool
{
	mutex mtx;
	vector<thread> threads;
	queue<function<void()>> waitingTasks;
	condition_variable cv;
	int maxWaiting;
	int initial_threads;
	bool stopSignal{ false };
public:
	ThreadPool(int initial_threads, int maxWaiting)
		: maxWaiting(maxWaiting), initial_threads(initial_threads){
		initializer();
	}
	~ThreadPool() {
		{
			lock_guard<mutex> lg(mtx);
			stopSignal = true;
		}
		cv.notify_all();
		for (auto& t : threads)
			t.join();
	}

	void add(function<void()> task) {
		if (waitingTasks.size() < maxWaiting) {
			lock_guard<mutex> lg(mtx);
			waitingTasks.push(task);
			cv.notify_one();
		}
		else {
			thread(task).detach();
		}
	}

	int getCurrentSizeOfThreads() {
		lock_guard<mutex> lg(mtx);
		return threads.size();
	}

private:
	void initializer() {
		for (int i{}; i < initial_threads; i++)
			threads.emplace_back([this]() {
				while (true)
				{
					function<void()> func;
					{
						unique_lock<mutex> ul(mtx);
						cv.wait(ul, [this] { return !waitingTasks.empty() || stopSignal; });
						if (stopSignal)
							break;
						func = waitingTasks.front();
						waitingTasks.pop();
					}
					func();
				}
			});
	}
};
