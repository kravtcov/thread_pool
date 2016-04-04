#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

typedef void (*Task)(void *);

class ThreadPool {
public:
    ThreadPool(int thread_num);
    ~ThreadPool();

    void post(Task task, void *task_data);

private:
    std::vector<std::thread> thread_pool;
    std::queue<Task> task_pool;

    std::mutex cv_m;
    std::condition_variable cv;
    // std::unique_lock<std::mutex> ul;

    void threadFunction(std::condition_variable &cv, std::mutex &cv_m);

};

