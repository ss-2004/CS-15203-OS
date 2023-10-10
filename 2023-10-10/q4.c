// Q4
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    sigset_t blk_msk;
    sigemptyset(&blk_msk);
    sigaddset(&blk_msk, SIGINT);

    if (sigprocmask(SIG_BLOCK, &blk_msk, NULL) == -1) {
        perror("sigprocmask\n");
        return 1;
    }

    printf("SIGINT signal ^C is blocked! Press ^C to test.\n");
    while (1) {
        printf("Performing random bg tasks...\n\n");
        sleep(2);
    }

    return 0;
}
