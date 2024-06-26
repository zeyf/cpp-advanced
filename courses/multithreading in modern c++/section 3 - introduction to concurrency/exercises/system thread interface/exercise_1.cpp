#include <thread>
#include <iostream>
#include <sstream>
#include <string>
#include <optional>

/*

std::thread ID
•Rewrite the "hello thread" program so it prints out the ID of the 
worker thread in the hello() function
•Modify the main() function to print out its own ID
•Modify the main() function to print out the ID of the hello thread
• Before calling join()
• After calling join()
•Explain your results

*/

void printThreadId(std::thread* thr) {
    std::stringstream ss;

    if (thr != nullptr) {
        ss << thr->get_id();
    } else {
        ss << std::this_thread::get_id();
    }
    std::cout << "Hello World from Thread ID #" << ss.str() << "\n";
}

int main() {
    std::stringstream ss;
    // Parent / main thread will have its own ID
    ss << std::this_thread::get_id();
    std::cout << "Main Thread ID # = " << ss.str() << "\n";
    
    // This thread ID should be the same as below, print thread is just the callable the thread is calling
    std::thread t{printThreadId, nullptr};
    // Should be the same as above
    printThreadId(&t);
    t.join();
    // When we join, we wait for the 't' thread to finish execution from the parent perspective
    // Therefore, the thread should be terminated after joining, and there should be no active address
    
    // No address
    printThreadId(&t);

    return 0;
}