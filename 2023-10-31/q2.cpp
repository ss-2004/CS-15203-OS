#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5
#define NUM_RESOURCES 3

int available[NUM_RESOURCES] = {2,1,0};
int maximum[NUM_THREADS][NUM_RESOURCES] = {{4,3,3}, {3,2,2}, {9,0,2}, {7,5,3}, {1,1,2}};
int allocation[NUM_THREADS][NUM_RESOURCES] = {{1,1,2}, {2,1,2}, {4,0,1}, {0,2,0}, {1,1,2}};
int need[NUM_THREADS][NUM_RESOURCES];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int isSafe(int thrd_id, int req[]){
    int work[NUM_RESOURCES];
    int finish[NUM_THREADS];
    int i,j;
    int safeSeq[NUM_THREADS], s=0;

    for(i=0; i<NUM_RESOURCES; i++)
        work[i] = available[i];
    for(int i=0; i<NUM_THREADS; i++)
        finish[i] = 0;
    
    for(int i=0; i<NUM_THREADS; i++){
        for(int j=0; j<NUM_RESOURCES; j++){
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    int num_finished = 0;
    while(num_finished < NUM_THREADS){
        int found = 0;
        for(int i=0; i< NUM_THREADS; i++){
            if(finish[i] == 0){
                int canAllocate = 1;
                for(int j = 0; j<NUM_RESOURCES; j++){
                    if(need[i][j] > work[i]){
                        canAllocate = 0;
                        break;
                    }
                }
                if(canAllocate){
                    for(int j=0; j<NUM_RESOURCES; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    safeSeq[s] = i;
                    s++;
                    found = 1;
                    num_finished++;
                }
            }
        }
        if(found == 0){
            return 0;
        }
    }

    printf("Safe sequence : ");
    for(int i = 0; i< NUM_THREADS; i++){
        printf("%d, ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

void reqRes(int thrd_id, int req[]){
    pthread_mutex_lock(&mutex);

    if(isSafe(thrd_id, req)){

    } else {

    }

    pthread_mutex_unlock(&mutex);
}

void relRes(int thrd_id, int release[]){
    pthread_mutex_lock(&mutex);



    pthread_mutex_unlock(&mutex);
}

void *threadfunc(void *arg){
    int thrd_id = *(int*)arg;
    int req[NUM_RESOURCES];
    int rel[NUM_RESOURCES];

    while(1){
        reqRes(thrd_id, req);
        relRes(thrd_id, rel);
        sleep(2);
    }

    pthread_exit(NULL);
}

int main(){
    int thrd_id[NUM_THREADS];
    pthread_t thrds[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for(int i=0; i<NUM_THREADS; i++){
        thrd_id[i] = i;
        pthread_create(&thrds[i], NULL, threadfunc, &thrd_id[i]);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(thrds[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}