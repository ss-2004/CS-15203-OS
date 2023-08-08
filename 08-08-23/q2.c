#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
// argv[2] = pattern
// argv[1] = file

void grep(char **pattern, char **filename) {
    char temp[200];
    FILE *fp;
    fp = fopen(filename, "r");
    while (!feof(fp)) {
        fgets(temp, 1000, fp);
        if (strstr(temp, pattern))
            printf("%s", temp);
    }
    fclose(fp);
}

void ls(char **dirname) {
    DIR *p;
    struct dirent *d;
    p = opendir(dirname);
    if (p == NULL) {
        perror("Cannot find directory");
        exit(-1);
    }
    while (d = readdir(p))
        printf("%s\n", d->d_name);
}


int main(int argc, char **argv) {
    //grep(argv[2], argv[1]);
    ls(argv[1]);
    return 0;
}
