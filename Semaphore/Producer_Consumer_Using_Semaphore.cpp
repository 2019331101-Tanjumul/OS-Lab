#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

using namespace std;

const int BUFFER_SIZE = 5;

vector<int> buffer(BUFFER_SIZE);
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
mutex mtx;

void produce(int item) {
    sem_wait(&empty);
    mtx.lock();
    buffer[in] = item;
    cout << "Produced Product ID. : " << item << endl;
    in = (in + 1) % BUFFER_SIZE;
    mtx.unlock();
    sem_post(&full);
}

void consume() {
    sem_wait(&full);
    mtx.lock();
    int item = buffer[out];
    cout << "Consumer Product ID. : " << item << endl;
    out = (out + 1) % BUFFER_SIZE;
    mtx.unlock();
    sem_post(&empty);
}

void producer() {
    for (int i = 1; i < 6; ++i) {
        produce(i);
        sleep(1);
    }
}

void consumer() {
    for (int i = 0; i < 5; ++i) {
        consume();
        sleep(2);
    }
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    thread producer_thread(producer);
    thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

