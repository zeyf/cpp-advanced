#include "thread_pool.h"
#include <iostream>
#include <functional>

int main() {

    non_idle_thread_pool<int> tp;
    for (int x = 0; x < 10; x++) {
        std::future<int> f = std::async(
            std::launch::deferred, // This makes the task run in the current thread that calls .get/.wait + similar
            [&x] () -> int {
                int return_value = x * 10;
                std::cout << return_value << "\n";
                return x * 10;
            }
        );
        tp.submit(&f);
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return 0;
}