//Q3
/*
 * Write a C program that deletes a directory with all its subfolders. The name of the directory should be read from the command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void deleteDirectory(const char *dirname) {
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

        if (remove(path) == -1) {
            perror("Error removing file");
        }
    }

    closedir(dir);

    if (rmdir(dirname) == -1) {
        perror("Error removing directory");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dirname = argv[1];

    deleteDirectory(dirname);

    printf("Directory '%s' and its subfolders have been deleted.\n", dirname);

    return EXIT_SUCCESS;
}