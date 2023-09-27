/**
 *  fork-wait-many
 *
 *  This program demonstrates using waitpid() in non-blocking mode, i.e., with
 *  the WNOHANG option.
 *
 *  The parent process first spawns 10 children, who each sleep for a random
 *  amount of time between 1s and 5s.
 *
 *  The parent will check for terminated children (i.e., zombies) every 0.5s,
 *  and reap all the zombies it can.  Note that if there happen to be multiple
 *  zombies, the parent will reap all of them before going back to sleep.
 */

// We need _GNU_SOURCE this to get access to random() and srandom().
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void child_task(long sleep_time) {

    // Sleep for a random amount of time.
    usleep(sleep_time);

    printf("    Child (PID = %d): about to exit after sleeping for %2fs\n",
            getpid(), sleep_time / 1000000.);

    exit(0);
}

int main(void) {
    int i;

    // Seed random number generator.
    srandom(time(NULL));

    // Spawn 10 children.
    for (i = 0; i < 10; i++) {
        // Random sleep time between 1s and 5s.
        long sleep_time = random() % 4000000 + 1000000;
        if (fork() == 0)
            child_task(sleep_time);
    }

    // At this point, i = 10, i.e., the number of children we have.

    // Loop until we reap all 10 children.
    while (i > 0) {

        // Sleep for 0.5s between checking waitpid().
        usleep(500000);

        printf("Parent: checking for any terminated children...\n");

        // Reap any zombies we encounter.
        pid_t pid;
        while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
            printf("Parent: reaped child %d/10 (PID = %d)\n", 10 - --i, pid);

        // waitpid() returns <= 0 when there are no more zombies to reap,
        // terminating the reap loop and allowing the parent to sleep again
        // before polling for zombies.
    }

    printf("Parent: reaped all children.\n");
    return 0;
}
