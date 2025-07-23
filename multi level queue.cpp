#include <stdio.h>

int main() {
    int n1, n2, tq;
    printf("Enter number of System (Queue 1) processes: ");
    scanf("%d", &n1);
    printf("Enter number of User (Queue 2) processes: ");
    scanf("%d", &n2);

    int total = n1 + n2;
    int pid[total], arrival[total], burst[total], remaining[total], queue[total];
    int completion[total], waiting[total], turnaround[total];
    int time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    // Input for Queue 1: Round Robin
    printf("\n--- Queue 1 (System Processes: Round Robin) ---\n");
    for (int i = 0; i < n1; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time and burst time for System P%d: ", pid[i]);
        scanf("%d%d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
        queue[i] = 1;
    }

    // Input for Queue 2: FCFS
    printf("\n--- Queue 2 (User Processes: FCFS) ---\n");
    for (int i = n1; i < total; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time and burst time for User P%d: ", pid[i]);
        scanf("%d%d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
        queue[i] = 2;
    }

    printf("\nEnter Time Quantum for Queue 1 (Round Robin): ");
    scanf("%d", &tq);

    int done[total];
    for (int i = 0; i < total; i++) done[i] = 0;

    int rr_index = 0, fcfs_index = 0;
    while (completed < total) {
        // --- Serve Queue 1 (Round Robin) ---
        int found = 0;
        for (int i = 0; i < total; i++) {
            if (queue[i] == 1 && arrival[i] <= time && remaining[i] > 0) {
                found = 1;
                if (remaining[i] > tq) {
                    time += tq;
                    remaining[i] -= tq;
                } else {
                    time += remaining[i];
                    remaining[i] = 0;
                    completion[i] = time;
                    turnaround[i] = completion[i] - arrival[i];
                    waiting[i] = turnaround[i] - burst[i];
                    total_wt += waiting[i];
                    total_tat += turnaround[i];
                    done[i] = 1;
                    completed++;
                }
            }
        }

        if (!found) {
            // --- Serve Queue 2 (FCFS) ---
            for (int i = 0; i < total; i++) {
                if (queue[i] == 2 && arrival[i] <= time && remaining[i] > 0) {
                    time += remaining[i];
                    remaining[i] = 0;
                    completion[i] = time;
                    turnaround[i] = completion[i] - arrival[i];
                    waiting[i] = turnaround[i] - burst[i];
                    total_wt += waiting[i];
                    total_tat += turnaround[i];
                    done[i] = 1;
                    completed++;
                    break; // FCFS: one at a time
                }
            }

            // If no process is ready in either queue
            if (!found && completed < total) {
                time++;
            }
        }
    }

    // --- Display Output ---
    printf("\nProcess\tQ\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < total; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], queue[i], arrival[i],
               burst[i], completion[i], turnaround[i], waiting[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", total_tat / total);
    printf("\nAverage Waiting Time = %.2f\n", total_wt / total);

    return 0;
}

