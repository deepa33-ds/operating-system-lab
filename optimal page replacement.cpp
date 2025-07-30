#include <stdio.h>

int main()
{
    int referenceString[50], frames[10];
    int n, frameCount;
    int i, j, k;
    int pageFaults = 0, count = 0;

    // Get input
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter number of frames available: ");
    scanf("%d", &frameCount);

    // Initialize frames with -1 (empty)
    for (i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }

    for (i = 0; i < n; i++)
    {
        int currentPage = referenceString[i];
        int found = 0;

        // Check if page already exists in frame
        for (j = 0; j < frameCount; j++)
        {
            if (frames[j] == currentPage)
            {
                found = 1;
                break;
            }
        }

        // If page is not found in memory (page fault)
        if (!found)
        {
            // If there is space in frame
            if (count < frameCount)
            {
                frames[count++] = currentPage;
            }
            else
            {
                int farthest = i + 1;
                int replaceIndex = -1;

                for (j = 0; j < frameCount; j++)
                {
                    int nextUse = -1;
                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == referenceString[k])
                        {
                            nextUse = k;
                            break;
                        }
                    }

                    // If not used again, best to replace
                    if (nextUse == -1)
                    {
                        replaceIndex = j;
                        break;
                    }

                    // Otherwise, choose the farthest use
                    if (nextUse > farthest)
                    {
                        farthest = nextUse;
                        replaceIndex = j;
                    }

                    if (replaceIndex == -1)
                        replaceIndex = 0;
                }

                // Replace page
                frames[replaceIndex] = currentPage;
            }

            pageFaults++;
        }

        // Print current frame status
        printf("After page %d -> ", currentPage);
        for (j = 0; j < frameCount; j++)
        {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
