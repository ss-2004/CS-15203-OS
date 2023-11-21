/*
 * Q3b :
 * The consumer process will then read and output the sequence from shared memory.
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

void *consumeCatalan(void *arg) {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHARED_MEM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    unsigned long long *shared_mem = (unsigned long long *) shmat(shmid, NULL, 0);
    if (shared_mem == (void *) -1) {
        perror("shmat");
        exit(1);
    }

    int n = *((int *) arg);
    printf("Consumer reading %d Catalan numbers from shared memory:\n", n);
    for (int i = 0; i < n; i++)
        printf("%llu ", shared_mem[i]);

    printf("\n");
    shmdt(shared_mem);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_catalan_numbers>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    pthread_t consumer_thread;

    pthread_create(&consumer_thread, NULL, consumeCatalan, &n);
    pthread_join(consumer_thread, NULL);
    return 0;
}
