#include <stdio.h>

int main() {
    int referenceString[50], frames[10], lastUsed[10];
    int n, frameCount;
    int i, j, k, time = 0;
    int pageFaults = 0, count = 0;

    // Input
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    // Initialize frames and last used times
    for (i = 0; i < frameCount; i++) {
        frames[i] = -1;
        lastUsed[i] = 0;
    }

    // Process each page request
    for (i = 0; i < n; i++) {
        int currentPage = referenceString[i];
        int found = 0;

        // Check if page is already in frames
        for (j = 0; j < frameCount; j++) {
            if (frames[j] == currentPage) {
                found = 1;
                time++;
                lastUsed[j] = time; // update usage time
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            // If there is empty space
            if (count < frameCount) {
                frames[count] = currentPage;
                time++;
                lastUsed[count] = time;
                count++;
            } else {
                // Find the least recently used page
                int lruIndex = 0;
                int minTime = lastUsed[0];

                for (j = 1; j < frameCount; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        lruIndex = j;
                    }
                }

                frames[lruIndex] = currentPage;
                time++;
                lastUsed[lruIndex] = time;
            }

            pageFaults++;
        }

        // Show frame state after each request
        printf("After page %d -> ", currentPage);
        for (k = 0; k < frameCount; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}

