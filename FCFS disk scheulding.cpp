#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i, totalMovement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    int request[n];

    printf("Enter the disk requests sequence: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nDisk head movement:\n");
    for (i = 0; i < n; i++) {
        printf("Move from %d to %d\n", head, request[i]);
        totalMovement += abs(request[i] - head);
        head = request[i];
    }

    printf("\nTotal Head Movement = %d\n", totalMovement);
    printf("Average Head Movement = %.2f\n", (float)totalMovement / n);

    return 0;
}

