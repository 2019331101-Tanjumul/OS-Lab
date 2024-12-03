#include <stack>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>

class Semaphore {
public:
    Semaphore(int count = 0) : count_(count) {}

    void notify() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++count_;
        if (!wait_stack_.empty()) {
            wait_stack_.top()->notify_one();
            wait_stack_.pop();
        }
    }

    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (count_ > 0) {
            --count_;
        } else {
            std::condition_variable* cv = new std::condition_variable();
            wait_stack_.push(cv);
            cv->wait(lock);
        }
    }

private:
    std::mutex mutex_;
    std::stack<std::condition_variable*> wait_stack_;
    int count_;
};

Semaphore sem(1);

void worker(int id) {
    sem.wait();
    std::cout << "Process " << id << " is working." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Process " << id << " is done." << std::endl;
    sem.notify();
}

int main() {
    const int num_processes = 10;
    std::thread processes[num_processes];

    for (int i = 0; i < num_processes; ++i) {
        processes[i] = std::thread(worker, i + 1);
    }

    for (int i = 0; i < num_processes; ++i) {
        processes[i].join();
    }

    return 0;
}
