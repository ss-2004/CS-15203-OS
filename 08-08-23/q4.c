//Q4
/*
 * Determine the size of a file using the lseek command. Once you found out the size, calculate the number of blocks assigned for the file. Compare these results with the similar results obtained when using the function stat.
 */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

void fileSizeLSEEK(char **filename) {
    int fd = open(filename, O_RDONLY);
    int size = lseek(fd, 0, SEEK_END);

    printf("LSEEK Size of %s = %d\n", filename, size);
    close(fd);
}

void fileSizeSTAT(char **filename) {
    struct stat stbuf;
    stat(filename, &stbuf);

    printf("STAT Size of %s = %d\n", filename, stbuf.st_size);
    printf("BLOCK Size of %s = %d\n", filename, stbuf.st_blocks);
    printf("BLOCK Size of %s = %d\n", filename, stbuf.st_ino);
}

int main(int argc, char **argv) {
    fileSizeLSEEK(argv[1]);
    fileSizeSTAT(argv[1]);
    return 0;
}
