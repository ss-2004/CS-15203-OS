#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int fd;
    char buff[100];
    fd = open("my_fifo.txt", O_RDONLY);
    
    if(fd == -1){
        perror("Failed to open FIFO for reading!\n");
        exit(1);   
    }
    
    ssize_t bytes_read = read(fd, buff, sizeof(buff));
    if(bytes_read > 0)
    	printf("Process 2 received data : %s\n", buff);
    
    close(fd);
	return 0;
}

