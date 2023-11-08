// Q3 : Write a program to implement signal handling.

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_hndlr(int signum) {
    printf("\n\tCaught SIGINT (^C)!\n\tExiting...\n");
    sleep(1);
    exit(1);
}

int main() {
    if (signal(SIGINT, sigint_hndlr) == SIG_ERR) {
        perror("signal\n");
        return 1;
    }

    printf("Press ^C for simulating interrupt SIGINT.\n");
    while (1) {
        printf("Performing random bg tasks...\n\n");
        sleep(2);
    }

    return 0;
}
