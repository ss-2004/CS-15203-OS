/* Q2
 * Write a program where child process sleeps for ‘2’seconds while the parent process waits for the child process to exit.
 * Note how return value of fork is used to control which code is run by parent and which by the child.
 * (Use if required:fork (), exec( ), wait( ), signal( ), kill( ), alarm( )system calls).
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t child_pid;
    int status;
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed!\n");
        exit(1);
    } else if (child_pid == 0) {
        printf("Child process (PID : %d) is sleeping...\n", getpid());
        sleep(2);
        printf("Child process (PID : %d) is running\n", getpid());
        exit(0);
    } else {
        printf("Parent process (PID : %d) is waiting for child process to exit.\n", getpid());
        waitpid(child_pid, NULL, 0);
        printf("Parent process (PID : %d) child has exited.\n", getpid());
    }
    return 0;
}

