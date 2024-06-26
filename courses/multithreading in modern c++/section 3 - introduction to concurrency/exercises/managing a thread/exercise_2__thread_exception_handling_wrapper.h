#include <thread>
#include <optional>
#include <sstream>
#include <string>


enum class ThreadDeconstructionPolicy {
    JOIN,
    DETACH
};


class InvalidThreadDeconstructionPolicyException: public std::exception {
private:
    char* message;
public:
    InvalidThreadDeconstructionPolicyException(char* msg): message(msg) {}
    char* what() {
        return message;
    }
};

// Very basic, but allows for retrieval
class ThreadExceptionHandlingWrapper {
private:
    std::thread* _thread;
    std::optional<std::exception> _exception;
    ThreadDeconstructionPolicy _threadDeconstructionPolicy;

public:
    ThreadExceptionHandlingWrapper(
        std::thread* thr,
        ThreadDeconstructionPolicy deconstructionPolicy
    ): _thread(thr), _threadDeconstructionPolicy(deconstructionPolicy) {};

    ~ThreadExceptionHandlingWrapper() {
        if (_thread->joinable()) {
            switch (_threadDeconstructionPolicy) {
                case ThreadDeconstructionPolicy::JOIN:
                    _thread->join();
                    std::cout << "Thread was joined as per policy" << "\n";
                    return;
                case ThreadDeconstructionPolicy::DETACH:
                    _thread->detach();
                    std::cout << "Thread was detached as per policy" << "\n";
                    return;
                default:
                    throw InvalidThreadDeconstructionPolicyException("Invalid ThreadDeconstructionPolicy applied.");
            }
        }
    }

    void setException(std::exception &e) {
        _exception.emplace(e);
    }

    std::optional<std::exception> getException() {
        return _exception;
    }

    std::thread* getThread() {
        return _thread;
    }
};
