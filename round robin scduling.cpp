#include <stdio.h>

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], arrival[n], burst[n], remaining[n], completion[n];
    int waiting[n], turnaround[n];
    int total_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    // Input burst and arrival times
    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time and burst time for process P%d: ", pid[i]);
        scanf("%d%d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0;
    int queue[n], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    // Enqueue the first process that arrives at time 0 or earliest
    for (int i = 0; i < n; i++) {
        if (arrival[i] == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            time++;
            for (int i = 0; i < n; i++) {
                if (arrival[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (remaining[idx] > 0) {
            if (remaining[idx] > quantum) {
                time += quantum;
                remaining[idx] -= quantum;
            } else {
                time += remaining[idx];
                remaining[idx] = 0;
                completion[idx] = time;
                turnaround[idx] = completion[idx] - arrival[idx];
                waiting[idx] = turnaround[idx] - burst[idx];
                total_wt += waiting[idx];
                total_tat += turnaround[idx];
                completed++;
            }

            // Enqueue newly arrived processes during execution
            for (int i = 0; i < n; i++) {
                if (arrival[i] > time - quantum && arrival[i] <= time && visited[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            // Re-enqueue the current process if it's not yet finished
            if (remaining[idx] > 0) {
                queue[rear++] = idx;
            }
        }
    }

    // Print results
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], arrival[i], burst[i],
               completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);

    return 0;
}

