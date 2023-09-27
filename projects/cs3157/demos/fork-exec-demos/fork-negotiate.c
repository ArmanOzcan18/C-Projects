/**
 *  A program that demonstrates the non-deterministic interleaving of two
 *  concurrent processes, personified as an argument between parent and child.
 *  (A little contrived, but so are all of the other examples...)
 *
 *  You should see different output each time you run this program; in
 *  particular, you should see the parent and child's print statements
 *  interleaved in a different order.
 *
 *  Also note that even though both processes apparently use the same "g"
 *  variable as a counter, they actually only manipulate their per-process copy
 *  of that variable after the fork().
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

int g;

int main(void) {

    pid_t pid = fork();

    if (pid < 0)
        die("fork");

    if (pid == 0) {
        /*
         * Child process
         */

        for (g = 60; g > 1; g--)
            printf("Child: Can I play for %d more minutes...\n", g);

    } else {
        /*
         * Parent process
         */

        for (g = 60; g > 1; g--)
            printf("Parent: No, and I'll only say this %d more times.\n", g);

    }

    return 0;
}
