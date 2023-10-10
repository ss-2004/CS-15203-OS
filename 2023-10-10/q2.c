// Q2
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int tot_proc = 0;
    int i;
    for (i = 1; i <= 10; i++) {
        pid_t childpid = fork();

        if (childpid == -1) {
            perror("fork\n");
            exit(1);
        }

        if (childpid == 0) {
            printf("Child process with PID : %d\n", getpid());
            exit(0);
        } else {
            wait(NULL);
            tot_proc++;
        }
    }

    FILE *file = fopen("p_manag.txt", "w");
    if (file == NULL) {
        perror("fopen\n");
        exit(1);
    }
    fprintf(file, "Total Processes : %d\n", tot_proc);
    fclose(file);

    system("cat p_manag.txt");
    return 0;
}
