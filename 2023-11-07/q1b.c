/*
 * Q1b :
 * Consider the Sleeping-Barber Problem with the modification that there are k barbers and k barber chairs
 * Write a program to coordinate the barbers and the customers.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define K 3

sem_t *customerSem, *barberSem, *accessSeatsSem, *barberSleepSem;
int waitingCustomers = 0;

void *barber(void *arg) {
    int id = *((int *) arg);

    while (1) {
        sem_wait(customerSem);
        sem_wait(accessSeatsSem);

        if (waitingCustomers > 0) {
            waitingCustomers--;

            sem_post(barberSem);
            sem_post(accessSeatsSem);


            printf("\n\tBarber %d is cutting hair.\n", id);
            sleep(2);

            printf("\n\tBarber %d finished cutting hair.\n", id);
        } else {
            sem_post(accessSeatsSem);
            printf("\n\tBarber %d is sleeping.\n", id);
            sem_wait(barberSleepSem);
        }
    }
}

void *customer(void *arg) {
    sem_wait(accessSeatsSem);

    if (waitingCustomers < N) {
        waitingCustomers++;
        printf("\n\tCustomer entered the waiting room.\n\tTotal customers waiting: %d\n", waitingCustomers);

        sem_post(customerSem);
        sem_post(accessSeatsSem);

        sem_wait(barberSem);
        printf("\n\tCustomer is getting a haircut.\n");
    } else {
        printf("\n\tNo available seats.\n\tCustomer is leaving.\n");
        sem_post(accessSeatsSem);
    }
}

int main() {
    pthread_t barberThreads[K], customerThread;
    int barberIDs[K];

    customerSem = sem_open("/customerSem", O_CREAT, 0644, 0);
    barberSem = sem_open("/barberSem", O_CREAT, 0644, 0);
    accessSeatsSem = sem_open("/accessSeatsSem", O_CREAT, 0644, 1);
    barberSleepSem = sem_open("/barberSleepSem", O_CREAT, 0644, 0);

    for (int i = 0; i < K; i++) {
        barberIDs[i] = i + 1;
        pthread_create(&barberThreads[i], NULL, barber, &barberIDs[i]);
    }

    for (int i = 0; i < 10; i++) {
        pthread_create(&customerThread, NULL, customer, NULL);
        sleep(1);
    }

    for (int i = 0; i < K; i++) {
        pthread_join(barberThreads[i], NULL);
    }

    sem_close(customerSem);
    sem_close(barberSem);
    sem_close(accessSeatsSem);
    sem_close(barberSleepSem);

    sem_unlink("/customerSem");
    sem_unlink("/barberSem");
    sem_unlink("/accessSeatsSem");
    sem_unlink("/barberSleepSem");

    return 0;
}
