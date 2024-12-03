#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <stdexcept>
#include <stack>
using namespace std;

class Semaphore {
public:
    Semaphore(int initial) : count(initial), max_count(initial) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mutex);
        if (count <= 0) {
            waiting_threads.push(std::this_thread::get_id());
            condition.wait(lock);
        }
        count--;
    }

    bool try_acquire_for(std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex);
        if (count <= 0) {
            waiting_threads.push(std::this_thread::get_id());
            if (condition.wait_for(lock, timeout) == std::cv_status::timeout) {
                return false;
            }
        }
        count--;
        return true;
    }

    void release() {
        std::lock_guard<std::mutex> lock(mutex);
        if (count >= max_count) {
            throw std::runtime_error("Semaphore count exceeded maximum limit");
        }
        count++;
        if (!waiting_threads.empty()) {
            auto id = waiting_threads.top();
            waiting_threads.pop();
            condition.notify_one();
        }
    }

    void resize(int new_max_count) {
        std::lock_guard<std::mutex> lock(mutex);
        max_count = new_max_count;
        if (count > max_count) {
            count = max_count;
        }
    }

private:
    int count;
    int max_count;
    std::mutex mutex;
    std::condition_variable condition;
    std::stack<std::thread::id> waiting_threads;
};

Semaphore sem(5);

void worker(int id) {
    if (sem.try_acquire_for(std::chrono::milliseconds(100))) {
        std::cout << "Worker " << id << " working.." << std::endl;
        std::cout << "Worker " << id << " done working." << std::endl;
        sem.release();
    } else {
        std::cout << "Worker " << id << " timed out while trying to do the job." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {
    std::thread threads[10];
    for (int i = 0; i < 10; ++i) {
        threads[i] = std::thread(worker, i);
    }

    for (int i = 0; i < 10; ++i) {
        threads[i].join();
    }

    return 0;
}
