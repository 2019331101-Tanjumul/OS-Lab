#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>
#include <numeric>

#include <unistd.h>



using namespace std;

struct Process {
    int pid;
    int arrival_time;
    double burst_time; // Using double to allow for fractional burst times
    int priority;
};

double Process1() {
    clock_t start = clock();
    for (int i = 0; i < 1500000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double Process2() {
    clock_t start = clock();
    for (int i = 0; i < 1000000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double Process3() {
    clock_t start = clock();
    for (int i = 0; i < 800000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

double Process4() {
    clock_t start = clock();
    for (int i = 0; i < 2000000000; ++i) {}
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

// Priority Scheduling Algorithm
pair<double, double> priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    double total_time = 0;
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);

    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority < b.priority;
    });

    for (int i = 0; i < n; ++i) {
        cout << processes[i].pid << " is running\n" ;
        sleep(1);
        total_time += processes[i].burst_time;
        waiting_time[i] = total_time - processes[i].burst_time;
        turnaround_time[i] = total_time;
    }

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;

    return {avg_waiting_time, avg_turnaround_time};
}
int main() {
    // Initialize processes
    vector<Process> processes;
    processes.push_back({1, 0, Process1(), 3});
    processes.push_back({2, 0, Process2(), 1});
    processes.push_back({3, 0, Process3(), 2});
    processes.push_back({4, 0, Process4(), 4});




    // Run Priority Scheduling
    cout << "\nPriority Scheduling:" << endl;
    pair<double, double> priority_results = priorityScheduling(processes);
    cout << "Burst times of the processes:" << endl;
    for (const auto& process : processes) {
        cout << "Process " << process.pid << ": " << process.burst_time << " seconds" << endl;
    }
    cout << "Average Waiting Time: " << priority_results.first << " seconds" << endl;
    cout << "Average Turnaround Time: " << priority_results.second << " seconds" << endl;

    return 0;
}

