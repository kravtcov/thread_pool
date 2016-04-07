#include "thread_pool.h"
#include <iostream>

template <typename T>
void task(void *task_data) {
    int data = *(int *)task_data;
    std::cout << "Task " << data << " is running" << std::endl;
    //std::this_thread::sleep_for(std::chrono::seconds(data % 10));

}

int main() {
    int thread_num = 1;
    ThreadPool pool(thread_num);


    return 0;
}

