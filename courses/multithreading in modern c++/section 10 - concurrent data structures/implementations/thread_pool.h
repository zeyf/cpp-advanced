#include <thread>
#include <mutex>
#include <condition_variable>
#include "concurrent_queue.h"
#include <vector>
#include <future>

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

template<typename T>
class non_idle_thread_pool {
private:
    // NOTE: std::thread::hardware_concurrency gives the number of cores...
    int _THREAD_COUNT = std::thread::hardware_concurrency();
    concurrent_queue<std::future<T>> _q;
    std::vector<std::thread> _threads;

    void _thread_listener() {
        while (true) {
            std::future<T> future = _q.pop();
            future.wait();
        }
    }
public:
    non_idle_thread_pool() {
        _threads = std::vector<std::thread>{std::move(std::thread{[this] () { this->_thread_listener(); }})};
    }
    void submit(std::future<T>& future) {
        _q.push(future);
    }
};

#endif