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
    double burst_time;
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

pair<double, double> roundRobin(vector<Process>& processes, int quantum) {
    int n = processes.size();
    queue<int> ready_queue;
    double total_time = 0;
    vector<double> remaining_time(n);
    vector<double> waiting_time(n, 0);
    vector<double> turnaround_time(n, 0);
    for (int i = 0; i < n; ++i)
        remaining_time[i] = processes[i].burst_time;

    cout << "Quantum Time: " << quantum << endl;
    cout << "Round Robin Scheduling:" << endl;

    while (true) {
        bool all_finished = true;
        for (int i = 0; i < n; ++i) {
            if (remaining_time[i] > 0) {
                all_finished = false;
                if (remaining_time[i] > quantum) {
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in ready queue" << endl;
                    total_time += quantum;
                    remaining_time[i] -= quantum;
                    sleep(1);
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in running queue" << endl;
                } else {
                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " in ready queue" << endl;
                    total_time += remaining_time[i];
                    double d = remaining_time[i];
                    sleep(1);
                    waiting_time[i] = total_time - processes[i].burst_time;
                    remaining_time[i] = 0;

                    cout << "Time: " << total_time << ", Process " << processes[i].pid << " completes execution" << endl;
                }
            }
        }
        if (all_finished) break;
    }

    for (int i = 0; i < n; ++i)
        turnaround_time[i] = processes[i].burst_time + waiting_time[i];

    double avg_waiting_time = accumulate(waiting_time.begin(), waiting_time.end(), 0.0) / n;
    double avg_turnaround_time = accumulate(turnaround_time.begin(), turnaround_time.end(), 0.0) / n;

    return {avg_waiting_time, avg_turnaround_time};
}


int main() {
    vector<Process> processes;
    processes.push_back({1, 0, Process1(), 3});
    processes.push_back({2, 0, Process2(), 1});
    processes.push_back({3, 0, Process3(), 2});
    processes.push_back({4, 0, Process4(), 4});

    int quantum = 1;



    cout << "Round Robin Scheduling:" << endl;
    pair<double, double> rr_results = roundRobin(processes, quantum);
    cout << "Burst times of the processes:" << endl;
    for (const auto& process : processes) {
        cout << "Process " << process.pid << ": " << process.burst_time << " seconds" << endl;
    }
    cout << "Average Waiting Time: " << rr_results.first << " seconds" << endl;
    cout << "Average Turnaround Time: " << rr_results.second << " seconds" << endl;

    return 0;
}
