#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define r 3
#define c 3
#define THRD 2

int A[r][c];
int B[r][c];
int add[r][c];
int sub[r][c];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *matAdd(void *arg){
	int tid = *((int*)arg);
	int ept = r/THRD;
    int start_row = tid * ept;
    int end_row = (tid == THRD - 1) ? r : (tid+1)*ept;
    int i, j;
    
    for(i=start_row; i<end_row; i++){
        for(j=0; j<c; j++){
            add[i][j] = A[i][j] + B[i][j];
        }
    }
    pthread_exit(NULL);
}

void *matSub(void *arg){
	int tid = *((int*)arg);
	int ept = r/THRD;
    int start_row = tid * ept;
    int end_row = (tid == THRD - 1) ? r : (tid+1)*ept;
    int i, j;
    
    for(i=start_row; i<end_row; i++){
        for(j=0; j<c; j++){
            sub[i][j] = A[i][j] - B[i][j];
        }
    }
    pthread_exit(NULL);
}

int main(){
	int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            A[i][j] = i+j;
            B[i][j] = i-j;
        }
    }
	pthread_t threads[THRD];
	int thrdID[THRD];
	
	for(i=0; i<THRD; i++){
	    thrdID[i] = i;
	    pthread_create(&threads[i], NULL, (i==0) ? matAdd : matSub, &thrdID[i]);
	}
	for(i=0; i<THRD; i++)
        pthread_join(threads[i], NULL);
	
    printf("Matrix A :\n");
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matrix B :\n");
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }
    
    printf("A+B :\n");
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d ", add[i][j]);
        }
        printf("\n");
    }

    printf("A-B :\n");
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d ", sub[i][j]);
        }
        printf("\n");
    }

    return 0;
}
