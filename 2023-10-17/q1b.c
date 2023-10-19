// Q1b : SJF

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int findSJ(int n, int bt[], int at[], int done[]) {
    int shortest = -1;
    int shortestTime = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!done[i] && at[i] <= 0) {
            if (bt[i] < shortestTime) {
                shortestTime = bt[i];
                shortest = i;
            }
        }
    }

    return shortest;
}

void findTAT(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findWT(int n, int bt[], int wt[], int at[]) {
    int done[n];
    int currT = 0;
    int remT = n;

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (remT > 0) {
        int shortest = findSJ(n, bt, at, done);

        if (shortest == -1) {
            currT++;
            continue;
        }

        wt[shortest] = currT - at[shortest];
        done[shortest] = 1;
        currT += bt[shortest];
        remT--;
    }
}

void findAvg(int n, int bt[], int at[]) {
    int wt[n], tat[n];
    float total_wt = 0, total_tat = 0;
    findWT(n, bt, wt, at);
    findTAT(n, bt, wt, tat);

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average Waiting Time: %.2f\n", (total_wt / n));
    printf("Average Turnaround Time: %.2f\n", (total_tat / n));
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burstTime[n];
    int arrivalTime[n];

    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &burstTime[i], &arrivalTime[i]);
    }

    findAvg(n, burstTime, arrivalTime);
    return 0;
}
