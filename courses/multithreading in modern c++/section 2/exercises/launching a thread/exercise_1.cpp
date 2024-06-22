#include <iostream>
#include <thread>

void helloWorld() {
    std::cout << "Hello World!" << "\n";
};

int main() {
    std::thread t(helloWorld);
    t.join();

    return 0;
}
