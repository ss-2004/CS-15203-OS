//Q2
/*
 * Write a C program that finds a file in a file-tree starting from a given directory. The name of the file for which we are searching for, as well as the name of the starting directory should be read from the command line. Optionally, the name of the file can be specified as a pattern using the * character.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

int match(const char *pattern, const char *filename) {

    if (*pattern == '\0' && *filename == '\0') {
        return 1;
    }

    if (*pattern == '*' && *(pattern + 1) != '\0' && *filename == '\0') {
        return match(pattern + 1, filename);
    }

    if (*pattern == *filename) {
        return match(pattern + 1, filename + 1);
    }

    return 0;
}

void searchFile(const char *dirname, const char *filename) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == -1) {
            perror("Error stat");
            continue;
        }

        if (S_ISDIR(statbuf.st_mode)) {
            searchFile(path, filename);
        } else if (S_ISREG(statbuf.st_mode)) {
            if (match(filename, entry->d_name)) {
                printf("Found: %s/%s\n", dirname, entry->d_name);
            }
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <starting_directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *startingDir = argv[2];

    searchFile(startingDir, filename);

    return EXIT_SUCCESS;
}
