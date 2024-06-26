#include <thread>
#include <iostream>
#include "exercise_2__thread_exception_handling_wrapper.h"


void hello() {
    std::cout << "Hello World from Thread" << "\n";
}


int main() {
    std::thread thr{hello};
    try {
        ThreadExceptionHandlingWrapper threadHandler(
            &thr,
            ThreadDeconstructionPolicy::JOIN
        );
        throw std::invalid_argument("Noooo!");
    } catch(std::invalid_argument& e) {}

    std::stringstream ss;
    ss << thr.get_id();
    std::cout << "After ThreadExceptionHandlingWrapper, thread ID = " << ss.str() << "\n";

    return 0;
}