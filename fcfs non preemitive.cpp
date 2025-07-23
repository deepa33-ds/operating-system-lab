#include <stdio.h>

int main() {
    int n, i, j;
    int pid[100], arrival_time[100], burst_time[100];
    int waiting_time[100], turnaround_time[100], completion_time[100];
    int total_wt = 0, total_tat = 0;
    int temp;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input process info
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time for Process %d: ", pid[i]);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time for Process %d: ", pid[i]);
        scanf("%d", &burst_time[i]);
    }

    // Sort by arrival time (simple bubble sort)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arrival_time[i] > arrival_time[j]) {
                // Swap arrival time
                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                // Swap burst time
                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                // Swap process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    int current_time = 0;

    // Calculate times
    for (i = 0; i < n; i++) {
        if (current_time < arrival_time[i])
            current_time = arrival_time[i]; // CPU idle until process arrives

        waiting_time[i] = current_time - arrival_time[i];
        completion_time[i] = current_time + burst_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];

        current_time += burst_time[i];

        total_wt += waiting_time[i];
        total_tat += turnaround_time[i];
    }

    // Print results
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n", pid[i], arrival_time[i], burst_time[i],
               waiting_time[i], turnaround_time[i], completion_time[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}

