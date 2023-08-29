/* Q6
 * Write a program that creates a child process.
 * Parent process writes data to 'pipe'
 * child process reads the data from pipe
 * prints data on the screen.
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int pipe_fd[2];
    char buff[100];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed!\n");
        exit(1);
    }
    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed!\n");
        exit(1);
    } else if (child_pid == 0) {
        close(pipe_fd[1]);
        ssize_t bytes_read = read(pipe_fd[0], buff, sizeof(buff));

        if (bytes_read > 0) {
            printf("Child process: \n\tReceived data from parent: %.*s\n", (int) bytes_read, buff);
        } else {
            printf("Child process: \n\tFailed to receive data from parent\n");
        }
        close(pipe_fd[0]);
    } else {
        close(pipe_fd[0]);
        const char *dataToSend = "Hello from Parent";
        ssize_t bytes_written = write(pipe_fd[1], dataToSend, strlen(dataToSend));

        if (bytes_written > 0) {
            printf("Parent process: \n\tSent data to Child: %s\n", dataToSend);
        } else {
            printf("Parent process: \n\tFailed to send data to Child\n");
        }
        close(pipe_fd[1]);
        wait(NULL);
    }
    return 0;
}

