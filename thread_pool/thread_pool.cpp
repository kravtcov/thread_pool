#include "thread_pool.h"
#include <iostream>
#include <cassert>

ThreadPool::ThreadPool(int thread_num) {

    assert(thread_num > 0);
    for (int i = 0; i < thread_num; i++) {
    //for ( auto &th : thread_pool) {
        thread_pool.push_back(std::thread(threadFunction, std::ref(this->task_pool),
                                          std::ref(cv), std::ref(cv_m)));
    }
}

ThreadPool::~ThreadPool() {

    cv.notify_all();
    for (int i = 0; i < thread_pool.size(); i++) {
        thread_pool[i].join();
    }
}

void threadFunction(std::queue<Task> &task_pool, std::condition_variable &cv, std::mutex &cv_m) {
    {
        std::lock_guard<std::mutex> lock(cv_m);
        std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
    }

    //while (true) {
    {
        {
            std::unique_lock<std::mutex> lk(cv_m);
            cv.wait(lk);
        }

        {
            std::lock_guard<std::mutex> lock(cv_m);
            Task task = task_pool.front();
            task_pool.pop();
            //void *data = data_pool.front();
        }

        std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));

        {
            std::lock_guard<std::mutex> lock(cv_m);
            std::cout << "done thread " << std::this_thread::get_id() << std::endl;
        }

    }

    {
        std::lock_guard<std::mutex> lock(cv_m);
        std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
    }

}

void ThreadPool::post(Task task, void *task_data) {
    {
        std::lock_guard<std::mutex> lock(cv_m);
        task_pool.push(task);
    }
    cv.notify_one();
}

