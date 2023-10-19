// Q1a : FCFS

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

void findWT(int n, int bt[], int wt[]) {
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];
}

void findTAT(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findAvg(int n, int bt[]) {
    int wt[n], tat[n];
    float total_wt = 0, total_tat = 0;
    findWT(n, bt, wt);
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
    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    findAvg(n, bt);
    return 0;
}
