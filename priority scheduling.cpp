#include <stdio.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], priority[n];
    int completion[n], waiting[n], turnaround[n];
    int is_completed[n];

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time, burst time and priority for process P%d: ", pid[i]);
        scanf("%d%d%d", &arrival[i], &burst[i], &priority[i]);
        is_completed[i] = 0;
    }

    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    while (completed != n) {
        int idx = -1;
        int highest_priority = 9999;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && is_completed[i] == 0) {
                if (priority[i] < highest_priority || 
                   (priority[i] == highest_priority && arrival[i] < arrival[idx])) {
                    highest_priority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time += burst[idx];
            completion[idx] = time;
            turnaround[idx] = completion[idx] - arrival[idx];
            waiting[idx] = turnaround[idx] - burst[idx];

            total_wt += waiting[idx];
            total_tat += turnaround[idx];
            is_completed[idx] = 1;
            completed++;
        } else {
            time++; // No process has arrived yet
        }
    }

    // Output the results
    printf("\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arrival[i], burst[i], priority[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}

