#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

void createFile(char *filename) {
    int fd;
    if ((fd = creat(filename, S_IRUSR | S_IWUSR)) < 0)
        perror("create() error");
    else {
        close(fd);
        printf("File %s created successfully\n", filename);
    }
}

void readFile(char *filename) {
    char str;
    int fd = open(filename, O_RDONLY);

    if (fd) {
        printf("\nFile contents : \n");
        while (read(fd, &str, 1) == 1) {
            printf("%c", str);
        }
    } else printf("File not found!");

    close(fd);
}

//void writeFile(char **filename) {
//    int fd;
//    if ((fd = creat(fn, S_IRUSR | S_IWUSR)) < 0)
//        perror("create() error");
//    else {
//        close(fd);
//        printf("File %s created successfully\n", filename);
//    }
//    return (fd);
//}
//
//void LinkUnlinkFile(char **filename) {
//    int fd;
//    if ((fd = creat(fn, S_IRUSR | S_IWUSR)) < 0)
//        perror("create() error");
//    else {
//        close(fd);
//        printf("File %s created successfully\n", filename);
//    }
//    return (fd);
//}
//
//void copyFile(char **filename) {
//    char buf;
//    int sourcefile, destfile, n;
//    sourcefile = open(argv[1], O_RDONLY);
//
//    if (sourcefile == -1) {
//        exit(0);
//    } else {
//        destfile = open(argv[2], O_WRONLY | O_CREAT, 0641);
//        if (destfile == -1) {
//            exit(0);
//        } else {
//            while ((n = read(sourcefile, &buf, 1)) != 0) {
//                write(destfile, &buf, 1);
//            }
//            write(STDOUT_FILENO, "FILES COPIED\n", 15);
//            close(sourcefile);
//            close(destfile);
//        }
//    }
//}
//
//void readRevFile(char **filename) {
//    int fd;
//    if ((fd = creat(fn, S_IRUSR | S_IWUSR)) < 0)
//        perror("create() error");
//    else {
//        close(fd);
//        printf("File %s created successfully\n", filename);
//    }
//    return (fd);
//}

int main(int argc, char **argv) {
    while (1) {
        printf("Press 0. EXIT\n"
               "Press 1. Create a file\n"
               "Press 2. Read contents of a file\n"
               "Press 3. Write to a file\n"
               "Press 4. Link and unlink a file\n"
               "Press 5. Copy file\n"
               "Press 6. Read contents of a file in a reverse order\n");

        int ch;
        printf("Enter choice : ");
        scanf("%d", &ch);
        char filename[1024] = "hello.txt";

        switch (ch) {
            case 0 :
                exit(ch);
                break;
            case 1 :
                printf("Enter filename to Create : ");
                scanf("%*[^\n]%*c", &filename);
                createFile(filename);
                break;
            case 2 :
                printf("Enter filename to Read : ");
                scanf("%*[^\n]%*c", &filename);
                readFile(filename);
                break;
            case 3 :
                break;
            case 4 :
                break;
            case 5 :
                break;
            case 6 :
                break;
            default:
                printf("INVALID INPUT!\n");
                break;
        }
        printf("\n");
    }
    return 0;
}