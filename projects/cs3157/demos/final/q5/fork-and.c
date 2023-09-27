#define _GNU_SOURCE   // for usleep()
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    if (fork() && fork()) {
        waitpid(-1, NULL, 0); // Wait for any child, no status, blocking
        printf("A\n");
    } else {
        // "Randomly" sleep() for 25 us to make the BAB outcome more likely.
        // if (getpid() % 2)   // UNCOMMENT ME
        //     usleep(20);     // UNCOMMENT ME
        printf("B\n");
    }
}
