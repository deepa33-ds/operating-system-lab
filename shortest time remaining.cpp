#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], remaining[n];
    int completion[n], waiting[n], turnaround[n];
    int total_completed = 0, time = 0;
    float total_waiting = 0, total_turnaround = 0;

    // Input arrival and burst times
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", pid[i]);
        scanf("%d%d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
    }

    while (total_completed != n) {
        int shortest = -1;
        int min_remaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (arrival[i] <= time && remaining[i] > 0 && remaining[i] < min_remaining) {
                min_remaining = remaining[i];
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        remaining[shortest]--;
        time++;

        if (remaining[shortest] == 0) {
            completion[shortest] = time;
            turnaround[shortest] = completion[shortest] - arrival[shortest];
            waiting[shortest] = turnaround[shortest] - burst[shortest];

            total_turnaround += turnaround[shortest];
            total_waiting += waiting[shortest];
            total_completed++;
        }
    }

    // Display result
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_turnaround / n);
    printf("\nAverage Waiting Time = %.2f\n", total_waiting / n);

    return 0;
}

