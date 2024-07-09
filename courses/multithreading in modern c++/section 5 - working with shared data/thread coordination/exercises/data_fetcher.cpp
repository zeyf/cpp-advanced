#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include <cstdlib>

/*
Multithreaded data fetching + progress bar simulation

Program design:
- Data fetcher
- Data progress bar
- Data processor -- post fetch

*/

std::mutex progressMtx;
std::mutex completionMtx;

int randInRange(int l, int r) {
    return l + (rand() % (r - l + 1));
}

void progressBar(int& progressCounter) {
    std::unique_lock<std::mutex> uLockForProgress{progressMtx, std::defer_lock};
    while (progressCounter < 100) {
        std::this_thread::sleep_for(
            std::chrono::seconds(
                randInRange(1, 2)
            )
        );
        uLockForProgress.lock();
        std::cout << "Progress: " << std::to_string(progressCounter) << "%" << "\n";
        uLockForProgress.unlock();
    }
}

void fetcher(int& progressCounter) {
    std::unique_lock<std::mutex> uLockForProgress{progressMtx, std::defer_lock};
    std::unique_lock<std::mutex> uLockForCompletion{completionMtx};

    while (progressCounter < 100) {
        std::this_thread::sleep_for(
            std::chrono::seconds(
                randInRange(1, 2)
            )
        );
        uLockForProgress.lock();
        // Converge towards 100% pseudo-randomly
        progressCounter += randInRange(1, (100 - progressCounter));
        uLockForProgress.unlock();
    }
}

void processor(int& progressCounter) {
    while (progressCounter < 100) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    // We use a scope lock to block locking until both are mutexes are released...
    std::scoped_lock(progressMtx, completionMtx);
    std::cout << "Processed the data!" << "\n";
}


int main() {
    srand(time(NULL));
    int progress = 0;
    std::thread f{fetcher, std::ref(progress)};
    std::thread pb{progressBar, std::ref(progress)};
    std::thread p{processor, std::ref(progress)};
    f.join(), pb.join(), p.join();

    std::cout << "Exiting main thread" << "\n";

    return 0;
}