#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void fileOp(){
    int fd;
    char data[] = "hello from";
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd == -1){
        perror("Error opening file!\n");
        exit(1);
    }
}

int main() {
	int fd;
    char data[] = "hello from ";
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    
    if(fd == -1){
        perror("Error opening file!\n");
        exit(1);
    }
	pid_t child_pid = fork();
	
	if(child_pid < 0) {
		perror("Fork failed!\n");
        exit(1);
	}	
    else if(child_pid == 0) {
		write(fd, strcat(data, "child\n"), sizeof(data) + sizeof("child") - 1);
	}
	else {
		write(fd, strcat(data, "parent\n"), sizeof(data) + sizeof("parent") - 1);
	}
	
	close(fd);
	system("cat output.txt");
	return 0;
}

