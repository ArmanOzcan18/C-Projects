/**
 *  fork-exec-myprogram
 *
 *  This program demonstrates using the fork()/waitpid() + exec() pattern to
 *  execute myprogram, which prints information about its PID, PPID, and args.
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

int main(void) {

    pid_t pid = fork();

    if (pid < 0)
        die("fork");

    if (pid == 0) {
        /*
         * Child process
         */

        char *argv[] = { "./myprogram", "-h", "-e", "-l", "-l", "-o", NULL };

        if (execv(argv[0], argv) == -1)
            die("execv");

        // UNREACHABLE

        printf("THIS SHOULD NEVER BE PRINTED\n");

    } else {
        /*
         * Parent process
         */

        printf("I (PID = %d) am waiting for my child (PID = %d)...\n",
            getpid(), pid);

        int ret;
        waitpid(pid, &ret, 0);

        printf("Child exited with status: %d\n", WEXITSTATUS(ret));
    }

    return 0;
}
