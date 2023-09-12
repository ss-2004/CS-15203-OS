
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000
#define THRD 4
#define KEY 42

int arr[SIZE];
int key = KEY;
int found = 0;
int ind = -1;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *searchEle(void *thrdID){
	int tid = *((int*)thrdID);
	int ept = SIZE/THRD;
    int start = tid * ept;
    int end = (tid == THRD - 1) ? SIZE : (tid+1)*ept;
    int i;
    
    for(i=start; i<end; i++){
        if(arr[i] == key){
            pthread_mutex_lock(&mutex);
            found = 1;
            ind = i;
            pthread_mutex_unlock(&mutex);
            break;
        }
    }
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
	    pthread_create(&threads[i], NULL, searchEle, &thrdID[i]);
	}
	for(i=0; i<THRD; i++)
        pthread_join(threads[i], NULL);
	
    if(found)
        printf("Element %d found at index : %d\n", key, ind);
    else
        printf("Element not found!");
    return 0;
}
