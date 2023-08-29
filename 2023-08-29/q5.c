/* Q5
 * In a C program, print the address of the variable and enter into a long loop (say using while (1)).
 * a.Start three to four processes of the same program and observe the printed address values.
 * b.Show how two processes which are members of the relationship parent-child are concurrent from execution point of view,
 * initially the child is copy of the parent, but every process has its own data.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int x = 0;
    int data = 42;
    printf("Parent Process ID: %d\n", getpid());
    printf("Parent - Address of data: %p\n", &data);

    for (int i = 0; i < 3; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (child_pid == 0) {
            printf("Child Process ID: %d\n", getpid());
            printf("Child - Address of data: %p\n", &data);
            data = i * 10;

            while (x < 1000000000) {
                x++;
            }

            printf("Child %d - Completed\n", i);
            exit(0);
        }
    }

    while (x < 1000000000) {
        x++;
    }

    printf("Parent - Completed\n");
    system("sleep 1");
    return 0;
}
