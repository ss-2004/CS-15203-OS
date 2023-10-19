// Q1c : Round Robin

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

struct Process {
    int id;
    int bt;
    int rt;
};


void findTAT(struct Process processes[], int n, int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = processes[i].bt;
    }
}

void findWT(struct Process processes[], int n, int wt[]) {
    int currT = 0;
    int remT = n;

    while (remT > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].rt > 0) {
                if (processes[i].rt <= 2) {
                    currT += processes[i].rt;
                    wt[i] = currT - processes[i].bt;
                    processes[i].rt = 0;
                    remT--;
                } else {
                    currT += 2;
                    processes[i].rt -= 2;
                }
            }
        }
    }
}

int main() {
    int n;
    float total_wt = 0, total_tat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    int tat[n];
    int wt[n];

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d: ", processes[i].id);
        scanf("%d", &processes[i].bt);
        processes[i].rt = processes[i].bt;
    }

    findWT(processes, n, wt);
    findTAT(processes, n, tat);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].bt, wt[i], tat[i]);
    }
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average Waiting Time: %.2f\n", (total_wt / n));
    printf("Average Turnaround Time: %.2f\n", (total_tat / n));
    return 0;
}
