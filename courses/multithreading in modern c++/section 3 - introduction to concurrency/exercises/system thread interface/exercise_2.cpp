#include <thread>
#include <iostream>
#include <chrono>

/*

Pausing a thread
•Modify the "Hello thread" program so that the thread pauses for two 
seconds before printing out the message

*/

void hello() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Hello World, but after a 2 second delay!" << "\n";
}

int main() {
    // no variable name declaration and join :P
    std::thread{hello}.join();

    return 0;
}