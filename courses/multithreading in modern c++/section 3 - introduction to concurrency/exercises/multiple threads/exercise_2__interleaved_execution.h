#include <thread>
#include <string>
#include <iostream>


class Printer {
public:
    void print(std::string s) {
        // Let's make as many explicit instructions to execute as possible...
        for (int x = 0; x < s.size(); x++)
            std::cout << s[x];
        std::cout << "\n";
    }
};

void InterleavedExecution() {
    Printer p;

    std::thread a{
        &Printer::print,
        &p,
        "Hello World"
    };

    std::thread b{
        &Printer::print,
        &p,
        "My first name is Zain"
    };

    std::thread c{
        &Printer::print,
        &p,
        "My last name is Yousaf Fuentes"
    };

    a.join(), b.join(), c.join();
}
