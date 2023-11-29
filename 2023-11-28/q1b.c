// Q1b : Write C programs to implement SCAN disk scheduling algorithms

#include <stdio.h>
#include <stdlib.h>

#define TOTAL_CYLINDERS 201
#define DIRECTION_RIGHT 1
#define DIRECTION_LEFT 0

void sortRequests(int req[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (req[i] > req[j]) {
                temp = req[i];
                req[i] = req[j];
                req[j] = temp;
            }
        }
    }
}

int findNextIndex(int req[], int n, int start, int direction) {
    int index = -1;
    if (direction == DIRECTION_RIGHT) {
        for (int i = start; i < n; i++) {
            if (req[i] >= 0) {
                index = i;
                break;
            }
        }
    } else {
        for (int i = start; i >= 0; i--) {
            if (req[i] >= 0) {
                index = i;
                break;
            }
        }
    }
    return index;
}

int calculateTotalDistance(int req[], int n, int start) {
    int totalDistance = 0;
    int direction = DIRECTION_RIGHT;
    int currentPos = start;

    sortRequests(req, n);
    int nextIndex = findNextIndex(req, n, 0, direction);

    while (nextIndex != -1) {
        totalDistance += abs(req[nextIndex] - currentPos);
        currentPos = req[nextIndex];
        req[nextIndex] = -1;

        if (currentPos == 0 || currentPos == TOTAL_CYLINDERS - 1)
            direction = !direction;

        if (direction == DIRECTION_RIGHT)
            nextIndex = findNextIndex(req, n, nextIndex + 1, direction);
        else
            nextIndex = findNextIndex(req, n, nextIndex - 1, direction);
    }

    return totalDistance;
}

int main() {
    int diskRequests[] = {30, 85, 90, 100, 105, 110, 135, 145};
    int numOfRequests = sizeof(diskRequests) / sizeof(diskRequests[0]);
    int currentHeadPos = 95;

    int totalDistance = calculateTotalDistance(diskRequests, numOfRequests, currentHeadPos);
    printf("Total distance moved by disk arm: %d cylinders\n\n", totalDistance);
    return 0;
}
