// Q3 : Find maximum element in the array using pthreads

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000
#define THRD 4

int arr[SIZE];
int max = INT_MIN;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *findMax(void *thrdID){
	int tid = *((int*)thrdID);
	int ept = SIZE/THRD;
    int start = tid * ept;
    int end = (tid == THRD - 1) ? SIZE : (tid+1)*ept;
    
    int i, loc_max = INT_MIN;
    
    for(i=start; i<end; i++){
        if(loc_max < arr[i])
            loc_max = arr[i];
    }
    
    pthread_mutex_lock(&mutex);
    if(loc_max > max)
        max = loc_max;
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
	    pthread_create(&threads[i], NULL, findMax, &thrdID[i]);
	}
	for(i=0; i<THRD; i++)
        pthread_join(threads[i], NULL);
	
    printf("Max element in array = %d\n", max);
    return 0;
}
