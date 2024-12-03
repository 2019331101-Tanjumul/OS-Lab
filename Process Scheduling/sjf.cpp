#include <stdio.h>

void sjf(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n];
    int temp_burst[n], remaining_processes = n;
    int time = 0, min_burst = 9999, shortest = -1;
    int flag = 0;

    // Initialize remaining burst times and waiting times
    for (int i = 0; i < n; i++) {
        temp_burst[i] = burst_time[i];
        waiting_time[i] = 0;
    }

    while (remaining_processes > 0) {
        min_burst = 9999;
        shortest = -1;
        // Find process with minimum burst time at the current time
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && temp_burst[i] < min_burst && temp_burst[i] > 0) {
                min_burst = temp_burst[i];
                shortest = i;
                flag = 1;
            }
        }

        if (flag == 0) {
            time++;
            continue;
        }

        // Reduce burst time of the selected process
        temp_burst[shortest]--;
        // Update minimum burst time
        min_burst = temp_burst[shortest];

        // If a process is completed
        if (min_burst == 0) {
            remaining_processes--;
            flag = 0;

            // Calculate finish time
            int finish_time = time + 1;

            // Calculate waiting time
            waiting_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];

            // Ensure waiting time is non-negative
            if (waiting_time[shortest] < 0) {
                waiting_time[shortest] = 0;
            }

            // Calculate turnaround time
            turnaround_time[shortest] = burst_time[shortest] + waiting_time[shortest];
        }

        // Move to the next time
        time++;
    }

    // Displaying process details
    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nTotal Waiting Time: %.2lf ms\n", total_waiting_time);
    printf("Average Waiting Time: %.2lf ms\n", total_waiting_time / n);
    printf("\nTotal Turnaround Time: %.2lf ms\n", total_turnaround_time);
    printf("Average Turnaround Time: %.2lf ms\n", total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burst_time[n];
    int arrival_time[n];

    // Input burst times and arrival times
    printf("Enter burst times and arrival times for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        processes[i] = i + 1; // Process numbers starting from 1
    }

    // Call SJF function
    sjf(processes, n, burst_time, arrival_time);

    return 0;
}
