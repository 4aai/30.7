#pragma once
#include <queue>
#include <future>
#include <condition_variable>
#include <vector>
#include <thread>
#include"BlockedQueue.h"


typedef std::function<void()> task_type;
typedef void (*FuncType) (std::shared_ptr<int[]>, long, long);
class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();
    void start();
    void stop();
    void push_task(FuncType f, std::shared_ptr<int[]> arr, long left, long right);
    void threadFunc(int qindex);
private:
    int m_thread_count = 0;
    std::vector<std::thread> m_threads;
    std::vector<BlockedQueue<task_type>> m_thread_queues;
    int m_index = 0;
};