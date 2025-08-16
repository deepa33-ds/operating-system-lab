#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, j, direction;
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

    printf("Enter head movement direction (1 = right, 0 = left): ");
    scanf("%d", &direction);

    // Add head into array
    int arr[n+1];
    for (i = 0; i < n; i++) arr[i] = request[i];
    arr[n] = head;
    int total = n + 1;

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

    if (direction == 1) { // Move right first
        // Service requests to the right
        for (i = headIndex; i < total; i++) {
            printf("Move to %d\n", arr[i]);
            if (i > headIndex)
                totalMovement += abs(arr[i] - arr[i-1]);
        }
        // Jump to the first request on the left
        if (headIndex > 0) {
            totalMovement += abs(arr[total-1] - arr[0]); // circular jump
            for (i = 0; i < headIndex; i++) {
                printf("Move to %d\n", arr[i]);
                if (i > 0)
                    totalMovement += abs(arr[i] - arr[i-1]);
            }
        }
    } else { // Move left first
        // Service requests to the left
        for (i = headIndex; i >= 0; i--) {
            printf("Move to %d\n", arr[i]);
            if (i < headIndex)
                totalMovement += abs(arr[i] - arr[i+1]);
        }
        // Jump to the last request on the right
        if (headIndex < total-1) {
            totalMovement += abs(arr[0] - arr[total-1]); // circular jump
            for (i = total-1; i > headIndex; i--) {
                printf("Move to %d\n", arr[i]);
                if (i < total-1)
                    totalMovement += abs(arr[i] - arr[i+1]);
            }
        }
    }

    printf("\nTotal Head Movement = %d\n", totalMovement);
    printf("Average Head Movement = %.2f\n", (float)totalMovement / n);

    return 0;
}

