#include <stdio.h>
#include <stdlib.h>

struct proc{
    int id;
    int priority;
    int bt;
}

void findWT(struct proc processes[], int n, int WT[]){
    WT[0] = 0;
    int i, j;
    for(i=0; i<n; i++){
        WT[i] = 0;
        for(j=0; i<n; j++){
            WT[i] += processes[j].bt;
        }
    }
}

void findTAT(struct proc processes[], int n, int WT[], int TAT[]){
    int i;
    for(i=0; i<n; i++){
        TAT[i] = processes[i].bt + WT[i];
    }
}

void findAvg(struct proc processes[], int n){
    int WT[n], TAT[n];
    int i, tot_WT=0, tot_TAT=0; 
    findWT(processes, n, WT);
    findTAT(processes, n, WT, TAT);

    printf("Process\tPriority\tBT\tWT\tTAT\n");
    for(i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].priority, processes[i].bt, WT[i], TAT[i]);
        tot_WT += WT[i];
        tot_TAT += TAT[i];
    }

    printf("Avg WT = %.2lf\n", (float)tot_WT/n);
    printf("Avg TAT = %.2lf\n", (float)tot_TAT/n);
}

int main(){
    int i, n;
    printf("Enter number of processes : ");
    scanf("%d", &n);

    struct proc processes[n];

    for(i=0; i<n; i++){
        processes[i].id = i+1;
        printf("Enter BT : ");
        scanf("%d", &processes[i].bt);
        printf("Enter priority : ");
        scanf("%d", &processes[i].priority);
    }
    findAvg(processes, n);
    return 0;
}
