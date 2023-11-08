/* Q1b
 * Server code executes the arithmetic operation. 
 * After the child (server) process finishes the operation, it transmits the result to parent process (client) 
 * Lastly, with the help of the system call exit. 
 * The client process prints the result on the screen and also reprints the prompter, ready for a new reading.
 * The read information is transmitted with the help of the system call execl to a child process
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    char op = argv[3][0];
    double result;

    if (op == 'e')
        exit(0);
    else if (op == '+')
        result = num1 + num2;
    else if (op == '-')
        result = num1 - num2;
    else if (op == '*')
        result = num1 * num2;
    else if (op == '/')
        result = num1 / num2;
    else if (op == '%')
        result = num1 % num2;
    else if (op == '^')
        result = pow(num1, num2);
    else {
        fprintf(stderr, "INVALID OPERATION %c !\n", op);
        exit(1);
    }

    printf("Result = %lf\n", result);
    return result;
}
