#include <thread>
#include <mutex>
#include <shared_mutex>
#include <iostream>
#include <vector>


class ThreadSafeVector {
private:
    std::shared_mutex shmtx;
    std::vector<int> _vec;

public:
    ThreadSafeVector(std::vector<int> &v): _vec(v) {};

    void push_back(int x) {
        // Without this, why would there be issues when pushing / printing multiple threads?
        // When pushing to a vector, it can be resized in between steps to accomodate for new elements that could be added to amortize the resize operation
        // Therefore, there will be garbage values during the resize that if there is no exc lock on the pushing, can result
        // in printing these garbage values that aren't really in the vector
        std::lock_guard<std::shared_mutex> exc_lock{shmtx};
        _vec.push_back(x);
    };

    // Still faces interleaving execution! -- This follows more of a reader-writer type of model
    void print() {
        // shared_lock + exc_log above solves issue of printing garbage values
        // However, even with this set up,
        // there can be interleaving of the prints due to the shared_lock policies / mechanisms
        
        std::shared_lock<std::shared_mutex> sh_lock{shmtx};
        for (int el: _vec) {
            std::cout << el << " ";
        }

        std::cout << "\n";
    }
};


void ThreadSafeMemoryLocation() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    ThreadSafeVector tsv{vec};

    std::thread a{
        &ThreadSafeVector::push_back,
        &tsv,
        10
    };

    std::thread b{
        &ThreadSafeVector::print,
        &tsv
    };

    std::thread c{
        &ThreadSafeVector::push_back,
        &tsv,
        42
    };

    std::thread d{
        &ThreadSafeVector::print,
        &tsv
    };

    a.join(), b.join(), c.join(), d.join();
}
