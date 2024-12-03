#include <iostream>
#include <mutex> // using mutex for sharing resources and synchronization 
#include <thread> // to create and manage therads 

using namespace std;

int main()
{
    const int no_of_philosophers = 5;

   //for chopstic structure this mu will use to lock acees to chopstic  
    struct Chopstics
    {
    public:
        Chopstics(){;}
        mutex mu;  // ensure only one philosopher can use the chopstic at a time 
    };

    auto eat = [](Chopstics &left_chopstics, Chopstics& right_chopstics, int philosopher_number) { // lamda function and assigning pholophors and passing the parameters 

        unique_lock<mutex> llock(left_chopstics.mu); //to lock the left and right mutex
        unique_lock<mutex> rlock(right_chopstics.mu);

        cout << "Philosopher " << philosopher_number << " is eating" << endl;

        chrono::milliseconds timeout(1500); // sleep of thread for 1500 ms 
        this_thread::sleep_for(timeout);

        cout << "Philosopher " << philosopher_number << " has finished eating" << endl;
    };

    Chopstics chp[no_of_philosophers]; // Array of chopsticks

    thread philosopher[no_of_philosophers]; // Array of philosophers

    cout << "Philosopher " << (0+1) << " is thinking.." << endl; //eating with the first and the last chopsticks
    philosopher[0] = thread(eat, ref(chp[0]), ref(chp[no_of_philosophers-1]), (0+1));

    for(int i = 1; i < no_of_philosophers; ++i) { // eating with the left chopsticks and the right chopsticks
        cout << "Philosopher " << (i+1) << " is thinking.." << endl;   
        philosopher[i] = thread(eat, ref(chp[i]), ref(chp[i-1]), (i+1));
    }

    for(auto &ph: philosopher) { // this auto function waits for all phil threads to finish before the program
        ph.join();
    }

    return 0;
}

