/*
 * Q2 :
 * Consider a system with three smoker processes and one agent process.
 * Each smoker continuously rolls a cigarette and then smokes it.
 * But to roll and smoke a cigarette, the smoker needs three ingredients: tobacco, paper, and matches.
 * One of the smoker processes has paper, another has tobacco, and the third has matches.
 * The agent has an infinite supply of all three materials.
 * The agent places two of the ingredients on the table.
 * The smoker who has the remaining ingredient then makes and smokes a cigarette, signalling the agent on completion.
 * The agent then puts out another two of the three ingredients, and the cycle repeats.
 * Write a program to synchronize the agent and the smokers.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t *agentSem, *tobaccoSem, *paperSem, *matchesSem;

void *agent(void *arg) {
    while (1) {
        sem_wait(agentSem);

        int random = rand() % 3;
        if (random == 0) {
            sem_post(tobaccoSem);
            sem_post(paperSem);
            printf("Agent placed tobacco and paper on the table.\n");
        } else if (random == 1) {
            sem_post(paperSem);
            sem_post(matchesSem);
            printf("Agent placed paper and matches on the table.\n");
        } else {
            sem_post(tobaccoSem);
            sem_post(matchesSem);
            printf("Agent placed tobacco and matches on the table.\n");
        }
    }
}

void *smoker_tobacco(void *arg) {
    while (1) {
        sem_wait(tobaccoSem);
        sem_wait(paperSem);
        printf("Smoker with tobacco is rolling and smoking the cigarette.\n");
        sem_post(agentSem);
    }
}

void *smoker_paper(void *arg) {
    while (1) {
        sem_wait(paperSem);
        sem_wait(matchesSem);
        printf("Smoker with paper is rolling and smoking the cigarette.\n");
        sem_post(agentSem);
    }
}

void *smoker_matches(void *arg) {
    while (1) {
        sem_wait(tobaccoSem);
        sem_wait(matchesSem);
        printf("Smoker with matches is rolling and smoking the cigarette.\n");
        sem_post(agentSem);
    }
}

int main() {
    pthread_t agentThread, smokerTobaccoThread, smokerPaperThread, smokerMatchesThread;

    agentSem = sem_open("/agentSem", O_CREAT, 0644, 1);
    tobaccoSem = sem_open("/tobaccoSem", O_CREAT, 0644, 0);
    paperSem = sem_open("/paperSem", O_CREAT, 0644, 0);
    matchesSem = sem_open("/matchesSem", O_CREAT, 0644, 0);

    pthread_create(&agentThread, NULL, agent, NULL);
    pthread_create(&smokerTobaccoThread, NULL, smoker_tobacco, NULL);
    pthread_create(&smokerPaperThread, NULL, smoker_paper, NULL);
    pthread_create(&smokerMatchesThread, NULL, smoker_matches, NULL);

    pthread_join(agentThread, NULL);
    pthread_join(smokerTobaccoThread, NULL);
    pthread_join(smokerPaperThread, NULL);
    pthread_join(smokerMatchesThread, NULL);

    sem_close(agentSem);
    sem_close(tobaccoSem);
    sem_close(paperSem);
    sem_close(matchesSem);

    sem_unlink("/agentSem");
    sem_unlink("/tobaccoSem");
    sem_unlink("/paperSem");
    sem_unlink("/matchesSem");

    return 0;
}
