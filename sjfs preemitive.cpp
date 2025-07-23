#include <stdio.h>
#define MAX 100

int main() {
    int n, i;
    int pid[MAX], arrival[MAX], burst[MAX], remaining[MAX];
    int waiting[MAX], turnaround[MAX], completion[MAX];
    int time = 0, completed = 0, min_index;
    int min_remaining, finish_time;
    float total_wt = 0, total_tat = 0;
    int is_process_running = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time for Process %d: ", pid[i]);
        scanf("%d", &arrival[i]);
        printf("Enter burst time for Process %d: ", pid[i]);
        scanf("%d", &burst[i]);
        remaining[i] = burst[i];
    }

    while (completed < n) {
        min_remaining = 1e9;
        min_index = -1;

        for (i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_remaining) {
                min_remaining = remaining[i];
                min_index = i;
            }
        }

        if (min_index != -1) {
            remaining[min_index]--;
            time++;

            if (remaining[min_index] == 0) {
                completed++;
                completion[min_index] = time;
                turnaround[min_index] = completion[min_index] - arrival[min_index];
                waiting[min_index] = turnaround[min_index] - burst[min_index];
                total_wt += waiting[min_index];
                total_tat += turnaround[min_index];
            }
        } else {
            // No process is ready; idle CPU
            time++;
        }
    }

    // Output results
    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t\t%d\n", pid[i], arrival[i], burst[i],
               waiting[i], turnaround[i], completion[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}

