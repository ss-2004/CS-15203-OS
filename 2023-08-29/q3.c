/* Q3
 * Write a program that calls fork()system call.
 * Before calling fork(), have the main process access a variable (e.g.,x) and set its value to something (e.g.,1000).
 * What value is the variable in the child process?
 * What happens to the variable when both the child and parent change the value of x?
 * Clearly write your observations.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int x = 1000;
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed!\n");
        exit(1);
    } else if (child_pid == 0) {
        printf("Child process before modification: x = %d\n", x);
        x = 2000;
        printf("Child process after modification: x = %d\n", x);
    } else {
        printf("Parent process before modification: x = %d\n", x);
        x = 3000;
        printf("Parent process after modification: x = %d\n", x);
    }
    return 0;
}

