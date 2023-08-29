#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
int main(){
	char cwd[256];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
    else
      printf("%s\n", cwd);
}
