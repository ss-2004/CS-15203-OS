/*
 * Q3a :
 * The producer process will generate the Catalan sequence and write it to a shared memory object.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX_SEQUENCE 100
#define SHARED_MEM_SIZE (MAX_SEQUENCE * sizeof(unsigned long long))

unsigned long long catalan[MAX_SEQUENCE];

void *produceCatalan(void *arg) {
    int n = *((int *) arg);

    catalan[0] = 1;
    for (int i = 1; i < n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - j - 1];
        }
    }

    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHARED_MEM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    unsigned long long *shared_mem = (unsigned long long *) shmat(shmid, NULL, 0);
    if (shared_mem == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    for (int i = 0; i < n; i++)
        shared_mem[i] = catalan[i];
    shmdt(shared_mem);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_catalan_numbers>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pthread_t producer_thread;

    pthread_create(&producer_thread, NULL, produceCatalan, &n);
    pthread_join(producer_thread, NULL);

    printf("Producer has generated the first %d Catalan numbers.\n", n);
    return 0;
}
