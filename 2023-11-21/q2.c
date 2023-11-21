/*
 * Q2 :
 * Write a program that implements the FIFO and LRU page-replacement algorithms.
 * First, generate a random page reference string where page numbers range from 0 to 9.
 * Apply the random page-reference string to each algorithm, and record the number of page faults incurred.
 * Implement the replacement algorithms so that the number of page frames can vary from 1 to 7.
 * Assume that demand paging is used.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool pageExists(int page, int *frames, int numFrames) {
    for (int i = 0; i < numFrames; ++i) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

int fifoPageReplacement(int *pages, int numPages, int numFrames) {
    int *frames = (int *) malloc(numFrames * sizeof(int));
    int pageFaults = 0;
    int frameIndex = 0;

    for (int i = 0; i < numPages; ++i) {
        if (!pageExists(pages[i], frames, numFrames)) {
            frames[frameIndex] = pages[i];
            frameIndex = (frameIndex + 1) % numFrames;
            pageFaults++;
        }
    }

    free(frames);
    return pageFaults;
}

int lruPageReplacement(int *pages, int numPages, int numFrames) {
    int *frames = (int *) malloc(numFrames * sizeof(int));
    int *counter = (int *) malloc(numFrames * sizeof(int));
    int pageFaults = 0;

    for (int i = 0; i < numFrames; ++i) {
        frames[i] = -1;
        counter[i] = 0;
    }

    for (int i = 0; i < numPages; ++i) {
        int j;
        for (j = 0; j < numFrames; ++j) {
            if (frames[j] == pages[i]) {
                counter[j] = i + 1;
                break;
            }
        }

        if (j == numFrames) {
            int leastUsed = 0;

            for (int k = 1; k < numFrames; ++k) {
                if (counter[k] < counter[leastUsed])
                    leastUsed = k;
            }

            frames[leastUsed] = pages[i];
            counter[leastUsed] = i + 1;
            pageFaults++;
        }
    }

    free(frames);
    free(counter);
    return pageFaults;
}

int main() {
    srand(time(NULL));
    int numPages = 30;
    int pages[numPages];

    for (int i = 0; i < numPages; ++i)
        pages[i] = rand() % 10;

    printf("Page reference string: ");
    for (int i = 0; i < numPages; ++i)
        printf("%d ", pages[i]);
    printf("\n");

    for (int numFrames = 1; numFrames <= 7; ++numFrames) {
        int fifoFaults = fifoPageReplacement(pages, numPages, numFrames);
        int lruFaults = lruPageReplacement(pages, numPages, numFrames);

        printf("\nNumber of frames: %d\n", numFrames);
        printf("FIFO Page Faults: %d\n", fifoFaults);
        printf("LRU Page Faults: %d\n", lruFaults);
    }

    return 0;
}
