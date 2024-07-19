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
    concurrent_queue<std::future<T>*> _q;
    std::vector<std::thread> _threads;
    std::atomic<bool> _shutdown = false;

    void _thread_listener() {
        while (!_shutdown) {
            std::future<T>* future = _q.pop();
            future->wait();
        }
    }

    void _init_threads() {
        for (int x = 0; x < _THREAD_COUNT; x++) {
            _threads.push_back(
                std::move(std::thread{[this](){ this->_thread_listener(); }})
            );
        }
    }
public:
    non_idle_thread_pool() {
        _init_threads();
    }

    void submit(std::future<T>* future) {
        _q.push(future);
    }

    ~non_idle_thread_pool() {
        _shutdown = true;
        for (std::thread& thr: _threads) {
            if (thr.joinable()) {
                thr.join();
            }
        }
    }
};

#endif