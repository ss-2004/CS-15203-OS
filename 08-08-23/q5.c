//Q5
/*
 * Write a program to change current working directory and display the inode details for each file in the new directory using the system calls: opendir( ), readdir( ), closedir( ), getcwd( ), chdir( ).
 */

#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/stat.h>

void printInodes(char **dirname) {
    DIR *dir;
    struct dirent *d;
    struct stat stbuf;
    char filename[1024];

    dir = opendir(dirname);
    if (dir == NULL) {
        perror("Cannot find directory");
        exit(-1);
    }

    while (d = readdir(dir)) {
        strcpy(filename, d->d_name);
        stat(filename, &stbuf);
        printf("Inode of %s : %d\n", filename, stbuf.st_ino);
    }

    closedir(dir);
}

int main(int argc, char **argv) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd() error\n");
    else {
        chdir(cwd);
        printInodes(cwd);
    }
    return 0;
}
