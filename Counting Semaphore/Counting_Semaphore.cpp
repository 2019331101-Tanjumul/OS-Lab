#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

class CountingSemaphore {
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    CountingSemaphore(int initialCount) : count(initialCount) {}

    void acquire() {
        unique_lock<mutex> lock(mtx);
        while (count <= 0) {
            cv.wait(lock);
        }
        count--;
    }

    void release() {
        lock_guard<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

CountingSemaphore semaphore(1); // Initialize with desired initial count

void P0() {
    semaphore.acquire();
    cout << "P0 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));

    cout << "P0 is finished.\n";
    semaphore.release();
}

void P1() {
    semaphore.acquire();
    cout << "P1 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    cout << "P1 is finished.\n";
    semaphore.release();
}

void P2() {
    semaphore.acquire();
    cout << "P2 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    cout << "P2 is finished.\n";
    semaphore.release();
}

void P3() {
    semaphore.acquire();
    cout << "P3 is executing.\n";
    // Critical section
    this_thread::sleep_for(chrono::seconds(1));
    cout << "P3 is finished.\n";
    semaphore.release();
}

int main() {
    thread t0(P0);
    thread t1(P1);
    thread t2(P2);
    thread t3(P3);

    t0.join();
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
