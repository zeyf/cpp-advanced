#include <thread>
#include <chrono>
#include <iostream>

void hello() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Hello World from Detached Thread!" << "\n";
}

int main() {
    std::cout << "Hello World from Main Thread!" << "\n";
    std::thread t{hello};
    t.detach();

    std::cout << "End of Main Thread" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
