#include <stdio.h>

int main()
{
    int referenceString[50], frames[10], freq[10], lastUsed[10];
    int n, frameCount;
    int i, j, k, time = 0;
    int pageFaults = 0, count = 0;

    // Input
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    // Initialize
    for (i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
        freq[i] = 0;
        lastUsed[i] = 0;
    }

    // Process reference string
    for (i = 0; i < n; i++)
    {
        int currentPage = referenceString[i];
        int found = 0;

        // Check if page is already present
        for (j = 0; j < frameCount; j++)
        {
            if (frames[j] == currentPage)
            {
                freq[j]++;
                time++;
                lastUsed[j] = time;
                found = 1;
                break;
            }
        }

        // Page Fault
        if (!found)
        {
            // If space available
            if (count < frameCount)
            {
                frames[count] = currentPage;
                freq[count] = 1;
                time++;
                lastUsed[count] = time;
                count++;
            }
            else
            {
                // Find LFU page (with LRU tie-breaker)
                int minFreq = freq[0], replaceIndex = 0;
                for (j = 1; j < frameCount; j++)
                {
                    if (freq[j] < minFreq)
                    {
                        minFreq = freq[j];
                        replaceIndex = j;
                    }
                    else if (freq[j] == minFreq)
                    {
                        if (lastUsed[j] < lastUsed[replaceIndex])
                        {
                            replaceIndex = j;
                        }
                    }
                }

                // Replace
                frames[replaceIndex] = currentPage;
                freq[replaceIndex] = 1;
                time++;
                lastUsed[replaceIndex] = time;
            }

            pageFaults++;
        }

        // Print current frame state
        printf("After page %d -> ", currentPage);
        for (k = 0; k < frameCount; k++)
        {
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
