#include <stdio.h>
#include <fcntl.h>	
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

void fileSizeLSEEK(char** filename){
	int fd = open(filename,O_RDONLY);
  	int size = lseek(fd, 0, SEEK_END);
  	printf("LSEEK Size of %s = %d\n", filename, size);
  	close(fd);	
}

void fileSizeSTAT(char** filename){
	struct stat stbuf;
	stat(filename, &stbuf);
	printf("STAT Size of %s = %d\n", filename, stbuf.st_size);
  	return 0;
}

int main(int argc, char** argv){
	fileSizeSTAT(argv[1]);
	fileSizeLSEEK(argv[1]);
   	return 0;	
}
