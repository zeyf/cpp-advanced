#include <thread>
#include <vector>
#include <iostream>


class NonThreadSafeVector {
private:
    std::vector<int> _vec;

public:
    NonThreadSafeVector(std::vector<int> &v): _vec(v) {};

    void push_back(int x) {
        _vec.push_back(x);
    };

    void print() {
        for (int el: _vec) {
            std::cout << el << " ";
        }

        std::cout << "\n";
    }
};

void NonThreadSafeMemoryLocation() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    NonThreadSafeVector ntsv{vec};

    std::thread a{
        &NonThreadSafeVector::push_back,
        &ntsv,
        10
    };

    std::thread b{
        &NonThreadSafeVector::print,
        &ntsv
    };

    std::thread c{
        &NonThreadSafeVector::push_back,
        &ntsv,
        42
    };

    std::thread d{
        &NonThreadSafeVector::print,
        &ntsv
    };

    a.join(), b.join(), c.join(), d.join();
}
