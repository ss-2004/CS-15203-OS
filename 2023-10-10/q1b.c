#include <cmath.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    char op = argv[3][0];
    double result;

    if (op == 'e')
        exit(0);
    else if(op == '+')
        result = num1 + num2;
    else if(op == '-')
        result = num1 - num2;
    else if(op == '*')
        result = num1 * num2;
    else if(op == '/')
        result = num1 / num2;
    else if(op == '%')
        result = num1 % num2;
    else if(op == '^')
        result = pow(num1, num2);
    else {
        fprintf(stderr, "INVALID OPERATION %c !\n", op);
        exit(1);
    }

    printf("Result = %lf\n", result);
    return result;
}