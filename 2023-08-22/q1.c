//Q1
/*
In this assignment we will start writing a command interpreter (Shell). The shell will give a prompt for the user to type in a command (from a set of commands), take the command, execute it, and then give the prompt back for the next command (i.e., actually give the functionality of a shell).
Your program should do the following:
Give a prompt "myshell$" for the user to type in a command Implement the following built in commands:
(a) cd < dir > : changes the directory to "dir"
(b) pwd : prints the current directory
(c) mkdir < dir > : creates a directory called "dir"
(d) rmdir < dir > : removes the directory called "dir"
(e) ls: lists the files in the current directory. It should support both ls without any option and with the option \-l"
(f) exit: exits the shell
The commands are the same as the corresponding Linux commands by the same name. Do "man" to see the descriptions. You can use the standard system calls chdir, getcwd, mkdir, rmdir, readdir etc. toimplement the calls (standard C library functions are available for these; look them up). These commands are called built in commands since your shell program will have a function correspondingto each of these commands to execute.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define PROMPT "myshell $ "
#define BUFFERSIZE 150

void CD(char *command) {
    char dirname[BUFFERSIZE / 3];
    strcpy(dirname, command + 3);
    int ret = chdir(dirname);
    if (ret)
        printf("%s: No such directory\n", dirname);
}

void PWD(char *command) {
    char cwd[BUFFERSIZE];
    getcwd(cwd, BUFFERSIZE);
    printf("%s\n", cwd);
}

void MKDIR(char *command) {
    char dirname[BUFFERSIZE / 3];
    strcpy(dirname, command + 6);
    int status = mkdir(dirname, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    if (status)
        printf("%s: Directory could not be created due to some error!\n", dirname);
}

void RMDIR(char *command) {
    char dirname[BUFFERSIZE / 3];
    strcpy(dirname, command + 6);
    int status = rmdir(dirname);
    if (status)
        printf("%s: Directory could not be removed due to some error!\n", dirname);
}

void LS(char *command) {
    struct dirent *dp;
    DIR *dirp = opendir(".");
    int count = 0;
    if (dirp != NULL) {
        while ((dp = readdir(dirp)) != NULL) {
            if (dp->d_name[0] != '.') {
                if (++count % 4)
                    printf("%-16s", dp->d_name);
                else
                    printf("%-16s\n", dp->d_name);
            }
        }

        closedir(dirp);
        if (count % 4 != 0)
            printf("\n");
        else
            printf("Could not get the files of the current directory\n");
    }
}

int main() {
    char command[BUFFERSIZE];
    int status;
    pid_t pid;

    while (1) {
        printf("%s", PROMPT);
        fgets(command, BUFFERSIZE, stdin);
        command[strlen(command) - 1] = '\0';

        if (strcmp(command, "exit") == 0)
            break;

        else if (strstr(command, "cd") != NULL) {
            CD(command);
        } else if (strcmp(command, "pwd") == 0) {
            PWD(command);
        } else if (strstr(command, "mkdir") != NULL) {
            MKDIR(command);
        } else if (strstr(command, "rmdir") != NULL) {
            RMDIR(command);
        } else if (strcmp(command, "ls") == 0) {
            LS(command);
        }
    }
}
