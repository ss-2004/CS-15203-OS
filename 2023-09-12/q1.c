
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000
#define THRD 4

int arr[SIZE];
int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *calcSum(void *thrdID){
	int tid = *((int*)thrdID);
	int ept = SIZE/THRD;
    int start = tid * ept;
    int end = (tid == THRD - 1) ? SIZE : (tid+1)*ept;
    
    int i, loc_sum = 0;
    
    for(i=start; i<end; i++){
        loc_sum += arr[i];
    }
    
    pthread_mutex_lock(&mutex);
    sum += loc_sum;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(){
	int i;
    for(i=0; i<SIZE; i++)
	    arr[i] = i+1;
	pthread_t threads[THRD];
	int thrdID[THRD];
	
	for(i=0; i< THRD; i++){
	    thrdID[i] = i;
	    pthread_create(&threads[i], NULL, calcSum, &thrdID[i]);
	}
	for(i=0; i<THRD; i++)
        pthread_join(threads[i], NULL);
	
    printf("Sum = %d\n", sum);
    return 0;
}
