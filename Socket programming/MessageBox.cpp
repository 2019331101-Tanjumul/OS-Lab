#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;
bool finished = false;
string message;

void sender() {
    while (!finished) {
        unique_lock<mutex> lck(mtx);
        cv.wait(lck, []{ return ready; });
        cout << "You: " << message << endl;
        ready = false;
        cv.notify_one();
    }
}

void receiver() {
    while (!finished) {
        unique_lock<mutex> lck(mtx);
        string input;
        getline(cin, input);
        message = input;
        ready = true;
        cv.notify_one();
        cv.wait(lck, []{ return !ready; });
    }
}

int main() {
    thread sender_thread(sender);
    thread receiver_thread(receiver);

    sender_thread.join();
    receiver_thread.join();

    return 0;
}
