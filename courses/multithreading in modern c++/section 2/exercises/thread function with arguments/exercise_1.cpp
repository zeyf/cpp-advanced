#include <iostream>
#include <thread>
#include <string>

class HelloWorldEnjoyer {
public:
    void hello() {
        std::cout << "Hello World from a Class method!" << "\n";
    }
};

void helloWorld() {
    std::cout << "Hello World from a regular function!" << "\n";
}

class Enjoyer {
public:
    Enjoyer(std::string x): _x(x) {}
 
    std::string operator()(std::string y) {
        std::cout << (_x + y);
        return _x + y;
    }
private:
    std::string _x;
};

int main() {
    // Regular
    std::thread t(helloWorld);

    // Prevent main thread from finishing earlier and data race with cout global
    t.join();


    // Lambda
    std::thread lambda{
        [&]() {
            std::cout << "Hello World from a lambda!" << "\n";
        }  
    };

    lambda.join();

    // Class member function
    HelloWorldEnjoyer enjoyer;
    std::thread classHello(&HelloWorldEnjoyer::hello, &enjoyer);

    classHello.join();


    // Functor (class with overloaded () operator)
    std::thread z(
        Enjoyer("Hello"),
        " World, I am in a class functor with an overloaded () operator!\n"
    );

    z.join();

    return 0;
}