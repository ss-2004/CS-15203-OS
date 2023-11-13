/*
 * Q1a :
 * Write a program to synchronize the sleeping barber problem to prevent any race conditions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t *barberSem, *customerSem, *accessSeatsSem, *barberSleepSem;
int waitingCustomers = 0;

void *barber(void *arg) {
    while (1) {
        sem_wait(barberSem);
        sem_wait(accessSeatsSem);

        waitingCustomers--;

        sem_post(barberSleepSem);
        sem_post(accessSeatsSem);

        printf("\n\tBarber is cutting hair.\n\n");
        sleep(2);
        printf("\n\tBarber finished cutting hair.\n\n");
    }
}

void *customer(void *arg) {
    sem_wait(accessSeatsSem);

    if (waitingCustomers < N) {
        waitingCustomers++;
        printf("\n\tCustomer entered the waiting room.\n\tTotal customers waiting: %d\n\n", waitingCustomers);

        sem_post(barberSem);
        sem_post(accessSeatsSem);

        sem_wait(barberSleepSem);
        printf("\n\tCustomer is getting a haircut.\n\n");
    } else {

        printf("\n\tNo available seats.\n\tCustomer is leaving.\n\n");
        sem_post(accessSeatsSem);
    }
}

int main() {
    pthread_t barberThread, customerThread;

    barberSem = sem_open("/barberSem", O_CREAT, 0644, 0);
    customerSem = sem_open("/customerSem", O_CREAT, 0644, 0);
    accessSeatsSem = sem_open("/accessSeatsSem", O_CREAT, 0644, 1);
    barberSleepSem = sem_open("/barberSleepSem", O_CREAT, 0644, 0);

    pthread_create(&barberThread, NULL, barber, NULL);

    for (int i = 0; i < 10; i++) {
        pthread_create(&customerThread, NULL, customer, NULL);
        sleep(1);
    }

    pthread_join(barberThread, NULL);

    sem_close(barberSem);
    sem_close(customerSem);
    sem_close(accessSeatsSem);
    sem_close(barberSleepSem);

    sem_unlink("/barberSem");
    sem_unlink("/customerSem");
    sem_unlink("/accessSeatsSem");
    sem_unlink("/barberSleepSem");

    return 0;
}
