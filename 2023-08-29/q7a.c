// UNRELATED PROCESSES

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int fd;
    fd = open("my_fifo.txt", O_WRONLY);

    if (fd == -1) {
        perror("Failed to open FIFO for writing!\n");
        exit(1);
    }

    const char *dataToSend = "Hello from process 1\n";
    write(fd, dataToSend, strlen(dataToSend) + 1);
    close(fd);
    return 0;
}

