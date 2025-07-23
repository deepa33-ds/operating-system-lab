#include <stdio.h>
#define MAX 100

int main() {
    int n, i, j;
    int pid[MAX], arrival_time[MAX], burst_time[MAX];
    int completion_time[MAX], waiting_time[MAX], turnaround_time[MAX];
    int completed[MAX] = {0};
    int total_wt = 0, total_tat = 0;
    int current_time = 0, min_index;
    int min_bt, found;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time for Process %d: ", pid[i]);
        scanf("%d", &arrival_time[i]);
        printf("Enter burst time for Process %d: ", pid[i]);
        scanf("%d", &burst_time[i]);
    }

    int completed_count = 0;
    while (completed_count < n) {
        found = 0;
        min_bt = 1e9;
        min_index = -1;

        // Find the shortest available job
        for (i = 0; i < n; i++) {
            if (!completed[i] && arrival_time[i] <= current_time && burst_time[i] < min_bt) {
                min_bt = burst_time[i];
                min_index = i;
                found = 1;
            }
        }

        if (found) {
            // Execute process
            current_time += burst_time[min_index];
            completion_time[min_index] = current_time;
            turnaround_time[min_index] = completion_time[min_index] - arrival_time[min_index];
            waiting_time[min_index] = turnaround_time[min_index] - burst_time[min_index];
            total_wt += waiting_time[min_index];
            total_tat += turnaround_time[min_index];
            completed[min_index] = 1;
            completed_count++;
        } else {
            // CPU idle
            current_time++;
        }
    }

    // Output
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n", pid[i], arrival_time[i], burst_time[i],
               waiting_time[i], turnaround_time[i], completion_time[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)total_tat / n);

    return 0;
}

