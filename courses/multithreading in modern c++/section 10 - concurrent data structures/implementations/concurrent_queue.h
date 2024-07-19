#include <mutex>
#include <thread>
#include <exception>
#include <queue>
#include <condition_variable>

#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

class concurrent_queue_is_empty_exception: std::logic_error {
public:
    concurrent_queue_is_empty_exception(): std::logic_error("Concurrent queue is empty. Cannot pop an element.") {}
    concurrent_queue_is_empty_exception(const char* s): std::logic_error(s) {}
};

template<typename T>
class concurrent_queue {
private:
    std::mutex _mtx;
    std::condition_variable _cv;
    std::queue<T> _q;
    // Used to prevent lossful wakeup and spurious wakeup on std::condition_variable
    bool not_empty = false;

public:
    concurrent_queue() {}
    void push(T& element) noexcept {
        std::lock_guard<std::mutex> lg{_mtx};
        _q.push(std::move(element));
        not_empty = true;
        _cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> uLock{_mtx};
        if (_q.size() == 0) {
            // throw concurrent_queue_is_empty_exception();
            _cv.wait(uLock, [&](){ return not_empty; });
        }

        T result = _q.front();
        _q.pop();
        return result;
    }
};

#endif