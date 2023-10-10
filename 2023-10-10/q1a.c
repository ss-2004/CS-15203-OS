#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    int num1, num2;
    char op;
    while(1){
        printf("Enter an operation : ");
        scanf("%c", &op);
        if(op == 'e'){
            printf("Program terminated!\n")
            exit(0);
        }
           
        printf("Enter two numbers : ");
        scanf("%d %d", &num1, &num2);
        pid_t childpid = fork();

        if(childpid == -1) {
            perror("fork\n");
            exit(1);
        }

        if(childpid == 0) {
            char num1_str[12], num2_str[12];
            sprintf(num1_str, "%d", num1);
            sprintf(num2_str, "%d", num2);
            char op_str[2] = {op, '\0'};

            execl("./q1b", "./q1b", num1_str, num2_str, op_str, (char*)NULL);
            perror("execl\n");
            exit(1);
        } else {
            int status;
            waitpid(childpid, &status, 0);
            if(WIFEXITED(status)) {
                double result = WIFEXITED(status);
                printf("Result from child process : %lf\n", result);
            } 
        }
    }
    return 0;
}
