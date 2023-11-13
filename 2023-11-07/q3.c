/*
 * Q3 :
 * Implement a solution to the Dining Philosophers problem using a monitor.
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/signal.h>

#define N 7
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N

void initialization();

void test(int i);

void take_chopsticks(int i);

void put_chopsticks(int i);

sem_t *mutex;
sem_t *next;

int next_count = 0;
int state[N];
int turn[N];

typedef struct {
    sem_t *sem;

    int count;
} condition;

condition x[N];

void wait_cust(int i) {
    x[i].count++;
    if (next_count > 0)
        sem_post(next);
    else
        sem_post(mutex);
    sem_wait(x[i].sem);
    x[i].count--;
}

void signal_cust(int i) {
    if (x[i].count > 0) {
        next_count++;
        sem_post(x[i].sem);
        sem_wait(next);
        next_count--;
    }
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING && turn[i] == i && turn[LEFT] == i) {
        state[i] = EATING;
        signal_cust(i);
    }
}

void take_chopsticks(int i) {
    sem_wait(mutex);
    state[i] = HUNGRY;
    test(i);

    while (state[i] == HUNGRY)
        wait_cust(i);

    if (next_count > 0)
        sem_post(next);
    else
        sem_post(mutex);

}

void put_chopsticks(int i) {
    sem_wait(mutex);
    state[i] = THINKING;

    turn[i] = RIGHT;
    turn[LEFT] = LEFT;

    test(LEFT);
    test(RIGHT);

    if (next_count > 0)
        sem_post(next);
    else
        sem_post(mutex);
}

void initialization() {
    int i;

    mutex = sem_open("/mutex", O_CREAT | O_EXCL, 0644, 1);
    next = sem_open("/next", O_CREAT | O_EXCL, 0644, 0);

    for (i = 0; i < N; i++) {
        state[i] = THINKING;
        char sem_name[20];
        snprintf(sem_name, sizeof(sem_name), "/sem_%d", i);
        x[i].sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 0);
        x[i].count = 0;
        turn[i] = i;
    }

    turn[1] = 2;
    turn[3] = 4;
    turn[6] = 0;
}

void cleanup() {
    int i;

    sem_close(mutex);
    sem_close(next);

    for (i = 0; i < N; i++) {
        char sem_name[20];
        snprintf(sem_name, sizeof(sem_name), "/sem_%d", i);
        sem_close(x[i].sem);
        sem_unlink(sem_name);
    }

    sem_unlink("/mutex");
    sem_unlink("/next");
}

void *philosopher(void *i) {
    while (1) {
        int self = *(int *) i;
        int j, k;

        j = rand();
        j = j % 11;

        printf("\n\tPhilosopher %d is thinking for %d secs\n", self, j);
        sleep(j);
        take_chopsticks(self);

        k = rand();
        k = k % 4;

        printf("\n\tPhilosopher %d is eating for %d secs\n", self, k);
        sleep(k);
        put_chopsticks(self);
    }
}

int main() {
    int i, pos[N];
    pthread_t thread[N];
    pthread_attr_t attr;

    initialization();
    pthread_attr_init(&attr);

    for (i = 0; i < N; i++) {
        pos[i] = i;
        pthread_create(&thread[i], NULL, philosopher, (int *) &pos[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread[i], NULL);
    cleanup();
    return 0;
}
