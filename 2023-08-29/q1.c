#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	pid_t child_pid;
	int status;
	child_pid = fork();
	
	if(child_pid < 0)
		perror("Fork failed!\n");
	else if(child_pid == 0) {
		printf("Child process (PID : %d) is running\n", getpid());
		exit(42);
	}
	else{
		waitpid(child_pid, &status, 0);
		printf("Child process (PID : %d) has terminated\n", child_pid);
		if(WIFEXITED(status)) {
		    printf("Termination status (DEC) : %d\n", WIFEXITED(status));
		    printf("Termination status (HEX) : 0x%X\n", WIFEXITED(status));
		}
		else {
		    printf("Child process did not terminate normally!\n");
		}
	}
	return 0;
}

