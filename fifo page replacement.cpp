#include <stdio.h>

int main()
{
    int referenceString[50], frames[10];
    int n, frameCount;
    int i, j, k;
    int pageFaults = 0, pointer = 0;

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

    // Initialize frames with -1
    for (i = 0; i < frameCount; i++)
    {
        frames[i] = -1;
    }

    // Process each page
    for (i = 0; i < n; i++)
    {
        int currentPage = referenceString[i];
        int found = 0;

        // Check if page is already in frame
        for (j = 0; j < frameCount; j++)
        {
            if (frames[j] == currentPage)
            {
                found = 1;
                break;
            }
        }

        // Page fault
        if (!found)
        {
            frames[pointer] = currentPage;
            pointer = (pointer + 1) % frameCount;
            pageFaults++;
        }

        // Show frame status
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
