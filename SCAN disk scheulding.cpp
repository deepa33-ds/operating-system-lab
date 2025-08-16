#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, size, direction;
    int totalMovement = 0;

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

    printf("Enter head movement direction (1 = right, 0 = left): ");
    scanf("%d", &direction);

    // Add head position to array
    int arr[n+1];
    for (i = 0; i < n; i++) arr[i] = request[i];
    arr[n] = head;

    // Sort requests
    for (i = 0; i < n+1; i++) {
        for (j = i+1; j < n+1; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Find head index
    int headIndex;
    for (i = 0; i < n+1; i++) {
        if (arr[i] == head) {
            headIndex = i;
            break;
        }
    }

    printf("\nDisk head movement:\n");

    if (direction == 1) { // Move right first
        for (i = headIndex; i < n+1; i++) {
            printf("Move to %d\n", arr[i]);
            if (i > headIndex)
                totalMovement += abs(arr[i] - arr[i-1]);
        }
        // Go to end of disk
        if (arr[n] != size-1) {
            totalMovement += abs((size-1) - arr[n]);
            printf("Move to %d (end)\n", size-1);
        }
        // Now go left
        for (i = headIndex-1; i >= 0; i--) {
            printf("Move to %d\n", arr[i]);
            if (i < headIndex-1)
                totalMovement += abs(arr[i] - arr[i+1]);
        }
    } else { // Move left first
        for (i = headIndex; i >= 0; i--) {
            printf("Move to %d\n", arr[i]);
            if (i < headIndex)
                totalMovement += abs(arr[i] - arr[i+1]);
        }
        // Go to start of disk
        if (arr[0] != 0) {
            totalMovement += abs(arr[0] - 0);
            printf("Move to 0 (start)\n");
        }
        // Now go right
        for (i = headIndex+1; i < n+1; i++) {
            printf("Move to %d\n", arr[i]);
            if (i > headIndex+1)
                totalMovement += abs(arr[i] - arr[i-1]);
        }
    }

    printf("\nTotal Head Movement = %d\n", totalMovement);
    printf("Average Head Movement = %.2f\n", (float)totalMovement / n);

    return 0;
}

