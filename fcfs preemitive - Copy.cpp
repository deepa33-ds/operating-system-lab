#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, j, time = 0, completed = 0, min_index;
    int arrival[100], burst[100], remaining[100], finish[100];
    int waiting[100], turnaround[100];
    float avg_wait = 0, avg_turnaround = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
    }

    printf("\nGantt Chart:\n");

    while (completed < n) {
        min_index = -1;
        int min_arrival = INT_MAX;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0) {
                if (min_index == -1 || remaining[i] < remaining[min_index]) {
                    min_index = i;
                }
            }
        }

        if (min_index == -1) {
            time++; // No process is ready to execute
            continue;
        }

        // Execute the process for 1 unit (preemptive)
        printf("| P%d ", min_index + 1);
        remaining[min_index]--;
        time++;

        if (remaining[min_index] == 0) {
            completed++;
            finish[min_index] = time;
            turnaround[min_index] = finish[min_index] - arrival[min_index];
            waiting[min_index] = turnaround[min_index] - burst[min_index];
            avg_wait += waiting[min_index];
            avg_turnaround += turnaround[min_index];
        }
    }

    printf("|\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wait / n);
    printf("\nAverage Turnaround Time = %.2f\n", avg_turnaround / n);

    return 0;
}

