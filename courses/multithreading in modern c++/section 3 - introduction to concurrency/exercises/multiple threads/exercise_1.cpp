#include <thread>
#include <iostream>
#include <chrono>

/*

Multiple Threads
•Write a program which starts three threads
•The thread function prints a message with a number related to the 
thread
•Each thread should sleep for a different amount of time before 
printing the message
• What purpose does sleeping achieve?

A: This simulates the concept of "context switching", showing that different threads that may have
been started at different times (potentially after others) may end before the first created thread
depending the work it needs to execute

*/

void hello(int x, std::chrono::milliseconds delay) {
    std::this_thread::sleep_for(delay);
    std::cout << "Hello from thread " << std::to_string(x) << "\n";
}

int main() {

    std::thread t{hello, 1, std::chrono::milliseconds(300)};
    std::thread u{hello, 2, std::chrono::milliseconds(100)};
    std::thread v{hello, 3, std::chrono::milliseconds(500)};

    t.join(), u.join(), v.join();

    return 0;
}