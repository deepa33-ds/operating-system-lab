#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, minIndex;
    int totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n], visited[n];

    printf("Enter the disk requests sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
        visited[i] = 0; // initially unvisited
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nDisk head movement:\n");

    for (i = 0; i < n; i++) {
        int minDist = 1e9; // large number
        minIndex = -1;

        // find nearest unvisited request
        for (j = 0; j < n; j++) {
            if (!visited[j]) {
                int dist = abs(head - request[j]);
                if (dist < minDist) {
                    minDist = dist;
                    minIndex = j;
                }
            }
        }

        // move head to nearest request
        printf("Move from %d to %d\n", head, request[minIndex]);
        totalMovement += abs(head - request[minIndex]);
        head = request[minIndex];
        visited[minIndex] = 1; // mark as visited
    }

    printf("\nTotal Head Movement = %d\n", totalMovement);
    printf("Average Head Movement = %.2f\n", (float)totalMovement / n);

    return 0;
}

