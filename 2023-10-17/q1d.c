// Q1d : Priority

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int findHYPR(int n, int priority[], int at[], int done[]) {
    int highest = -1;
    int highestPriority = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (!done[i] && at[i] <= 0) {
            if (priority[i] < highestPriority) {
                highestPriority = priority[i];
                highest = i;
            }
        }
    }

    return highest;
}

void findTAT(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findWT(int n, int bt[], int wt[], int at[], int priority[]) {
    int done[n];
    int currentTime = 0;
    int rem = n;

    for (int i = 0; i < n; i++)
        done[i] = 0;

    while (rem > 0) {
        int highest = findHYPR(n, priority, at, done);
        if (highest == -1) {
            currentTime++;
            continue;
        }

        wt[highest] = currentTime - at[highest];
        done[highest] = 1;
        currentTime += bt[highest];
        rem--;
    }
}

void findAvg(int n, int bt[], int at[], int priority[]) {
    int wt[n], tat[n];
    float total_wt = 0, total_tat = 0;
    findWT(n, bt, wt, at, priority);
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

    int bt[n];
    int at[n];
    int priority[n];

    printf("Enter burst time, arrival time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &bt[i], &at[i], &priority[i]);
    }

    findAvg(n, bt, at, priority);
    return 0;
}
