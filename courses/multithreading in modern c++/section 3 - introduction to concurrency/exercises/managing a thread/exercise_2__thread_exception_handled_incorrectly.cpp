#include <thread>
#include <iostream>
#include <sstream>

/*

Will this program work as expected?
•Explain your answer
int main() {
    try {
        std::thread thr(hello);
        throw std::exception();
        thr.join();
    } catch (std::exception& e) {
        std::cout << "Exception caught\n";
    }
}

A: No, because the thread will not be joined...
The exception would a jump to the end of the try block, the main thread would not wait for the thread to finish execution and will start destructing objects like thread thr and so on
Also, we would never hit the join on the thread, so that thread would never finish execution if the main thread finishes earlier
*/

void hello(std::thread::id* t_id_placeholder) {
    *t_id_placeholder = std::this_thread::get_id();
    std::cout << "Hello World from Thread!" << "\n";

    // This will result in an exception to std::terminate which ultimately calls std::abort
    // In the case that there is an abort, the entire program is terminated -- you have to catch any and all exceptions possible!
    throw std::exception();
}

int main() {
    std::thread::id t_id;
    try {
        std::thread thr(hello, &t_id);

    // The catch block will not be reached -- An uncaught exception in a thread terminates all threads
    } catch (std::exception& e) {
        std::stringstream ss;
        ss << t_id;
        std::cout << "Exception caught in thread " << ss.str() << "\n";
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}
