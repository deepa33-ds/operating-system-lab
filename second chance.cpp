#include <stdio.h>

int main()
{
    int n, framesCount;
    int referenceString[100];
    int frames[10], refBit[10];
    int i, j, pageFaults = 0, pointer = 0;

    // Input
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &referenceString[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &framesCount);

    // Initialize frames and reference bits
    for (i = 0; i < framesCount; i++)
    {
        frames[i] = -1;
        refBit[i] = 0;
    }

    // Process reference string
    for (i = 0; i < n; i++)
    {
        int currentPage = referenceString[i];
        int found = 0;

        // Check if page already in frame
        for (j = 0; j < framesCount; j++)
        {
            if (frames[j] == currentPage)
            {
                refBit[j] = 1; // give second chance
                found = 1;
                break;
            }
        }

        // Page fault handling
        if (!found)
        {
            while (1)
            {
                if (refBit[pointer] == 0)
                {
                    // Replace page at pointer
                    frames[pointer] = currentPage;
                    refBit[pointer] = 1; // set reference bit
                    pointer = (pointer + 1) % framesCount;
                    break;
                }
                else
                {
                    refBit[pointer] = 0;
                    pointer = (pointer + 1) % framesCount;
                }
            }

            pageFaults++;
        }

        // Show frame state
        printf("After page %d -> ", currentPage);
        for (j = 0; j < framesCount; j++)
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
