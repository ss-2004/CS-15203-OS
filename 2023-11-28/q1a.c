// Q1a : Write C programs to implement FCFS disk scheduling algorithms

#include <stdio.h>
#include <stdlib.h>

int calculateTotalMovement(int initialPosition, int requestQueue[], int numOfRequests) {
    int totalMovement = 0;
    int currentPosition = initialPosition;

    for (int i = 0; i < numOfRequests; ++i) {
        int distance = abs(requestQueue[i] - currentPosition);
        totalMovement += distance;
        currentPosition = requestQueue[i];
    }

    return totalMovement;
}

int main() {
    int diskSize = 201;
    int initialPosition = 95;
    int requestQueue[] = {30, 85, 90, 100, 105, 110, 135, 145};

    int numOfRequests = sizeof(requestQueue) / sizeof(requestQueue[0]);
    int totalMovement = calculateTotalMovement(initialPosition, requestQueue, numOfRequests);

    printf("Total distance moved by the disk arm using FCFS: %d cylinders\n\n", totalMovement);
    return 0;
}
