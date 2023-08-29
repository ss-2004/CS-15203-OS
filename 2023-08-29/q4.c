/* Q4
 * Write a program that opens a file (with the open() system call) 
 * and then calls fork()to create a new process.
 * Can both the child and parent access the file descriptor returned by open()?
 * What happens when they are writing to the file concurrently, i.e., at the same time?
 * Clearly write your observations.
 */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int fd;
    pid_t child_pid;
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed!\n");
        exit(1);
    } else if (child_pid == 0) {
        const char *child_message = "Hello from child!\n";
        write(fd, child_message, strlen(child_message));
    } else {
        const char *parent_message = "Hello from parent!\n";
        write(fd, parent_message, strlen(parent_message));
    }

    close(fd);
    system("cat output.txt");
    return 0;
}

