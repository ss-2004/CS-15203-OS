// Q2 : SRTF

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct Process {
    int id;
    int at;
    int bt;
    int remT;
    int ct;
};

int findSJ(struct Process *processes, int n, int currT) {
    int shortestJob = -1;
    int shortestTime = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (processes[i].at <= currT && processes[i].remT < shortestTime &&
            processes[i].remT > 0) {
            shortestTime = processes[i].remT;
            shortestJob = i;
        }
    }

    return shortestJob;
}

void findTAT(struct Process *processes, int n, int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = processes[i].ct - processes[i].at;
    }
}

void findWT(struct Process *processes, int n, int wt[]) {
    for (int i = 0; i < n; i++) {
        wt[i] = processes[i].ct - processes[i].at - processes[i].bt;
    }
}

int main() {
    int n;
    float total_wt = 0, total_tat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *) malloc(n * sizeof(struct Process));
    int *tat = (int *) malloc(n * sizeof(int));
    int *wt = (int *) malloc(n * sizeof(int));

    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
        processes[i].id = i + 1;
        processes[i].remT = processes[i].bt;
    }

    int currT = 0;
    int completed = 0;

    while (completed < n) {
        int shortestJob = findSJ(processes, n, currT);

        if (shortestJob == -1) {
            currT++;
        } else {
            processes[shortestJob].remT--;

            if (processes[shortestJob].remT == 0) {
                completed++;
                processes[shortestJob].ct = currT + 1;
            }

            currT++;
        }
    }

    findTAT(processes, n, tat);
    findWT(processes, n, wt);

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].at, processes[i].bt,
               processes[i].ct, tat[i], wt[i]);
    }
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("Average Waiting Time: %.2f\n", (total_wt / n));
    printf("Average Turnaround Time: %.2f\n", (total_tat / n));
    free(processes);
    free(tat);
    free(wt);
    return 0;
}
