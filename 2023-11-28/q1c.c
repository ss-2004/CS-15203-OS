// Q1c : Write C programs to implement SSTF disk scheduling algorithms
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TOTAL_CYLINDERS 201

int findShortestSeekTime(int req[], int n, int currentPos, int visited[]) {
    int minDistance = INT_MAX;
    int nextIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            int distance = abs(req[i] - currentPos);
            if (distance < minDistance) {
                minDistance = distance;
                nextIndex = i;
            }
        }
    }

    return nextIndex;
}

int calculateTotalDistance(int req[], int n, int start) {
    int totalDistance = 0;
    int currentPos = start;
    int visited[n];

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    for (int i = 0; i < n; i++) {
        int nextIndex = findShortestSeekTime(req, n, currentPos, visited);
        totalDistance += abs(req[nextIndex] - currentPos);
        currentPos = req[nextIndex];
        visited[nextIndex] = 1;
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
