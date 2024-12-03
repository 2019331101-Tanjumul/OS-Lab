#include <stdio.h>

void fcfs(int processes[], int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n];
  
    waiting_time[0] = 0; // First process has 0 waiting time
  
    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + burst_time[i - 1];
    }
  
    // Calculating turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }
  
    // Displaying process details
    printf("Process\t\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    double total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        waiting_time[i]-=arrival_time[i];
        turnaround_time[i]-=arrival_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nTotal Waiting Time: %.2lf ms\n", total_waiting_time);
    printf("Average Waiting Time: %.2lf ms\n", total_waiting_time / n);
    printf("\nTotal Turnaround Time: %.2lf ms\n",total_turnaround_time);
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
  
    // Call FCFS function
    fcfs(processes, n, burst_time, arrival_time);
  
    return 0;
}
