#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, size, i, j, totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter the disk requests sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (max track number): ");
    scanf("%d", &size);

    // Add head, 0 and end of disk to request list
    int arr[n + 3];
    for (i = 0; i < n; i++) arr[i] = request[i];
    arr[n] = head;
    arr[n+1] = 0;         // beginning of disk
    arr[n+2] = size - 1;  // end of disk

    int total = n + 3;

    // Sort requests
    for (i = 0; i < total; i++) {
        for (j = i+1; j < total; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find head index
    int headIndex;
    for (i = 0; i < total; i++) {
        if (arr[i] == head) {
            headIndex = i;
            break;
        }
    }

    printf("\nDisk head movement:\n");

    // Move right first
    for (i = headIndex; i < total; i++) {
        printf("Move to %d\n", arr[i]);
        if (i > headIndex)
            totalMovement += abs(arr[i] - arr[i-1]);
    }

    // Jump from end of disk to beginning
    totalMovement += (size - 1 - 0);
    printf("Jump from %d to 0\n", size - 1);

    // Continue moving right again from start
    for (i = 0; i < headIndex; i++) {
        printf("Move to %d\n", arr[i]);
        if (i > 0)
            totalMovement += abs(arr[i] - arr[i-1]);
    }

    printf("\nTotal Head Movement = %d\n", totalMovement);
    printf("Average Head Movement = %.2f\n", (float)totalMovement / n);

    return 0;
}

