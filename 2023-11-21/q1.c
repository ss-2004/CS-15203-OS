/*
 * Q1 :
 * Write a C program that is passed a virtual address on the CLI
 * Output the page number and offset for the given address
 */

#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096

void getPageNumberAndOffset(unsigned int address) {
    unsigned int pageNumber = address / PAGE_SIZE;
    unsigned int offset = address % PAGE_SIZE;

    printf("The address %u contains : \n", address);
    printf("page number = %u\n", pageNumber);
    printf("offset = %u\n", offset);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <virtual_address>\n", argv[0]);
        return 1;
    }

    unsigned int virtualAddress = atoi(argv[1]);
    getPageNumberAndOffset(virtualAddress);

    return 0;
}
