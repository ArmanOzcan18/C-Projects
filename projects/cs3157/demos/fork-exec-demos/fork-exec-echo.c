/**
 *  fork-exec-echo
 *
 *  This program demonstrates using the fork()/waitpid() + exec() pattern to
 *  execute another program.  The program fork()s; the child exec()s into the
 *  echo program, while the parent waits for the child to terminate.  The parent
 *  finally reports the child's status code.
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

        char *argv[] = { "/usr/bin/echo", "hello", NULL };

        if (execv(argv[0], argv) == -1)
            die("execv");

        // UNREACHABLE

        printf("THIS SHOULD NEVER BE PRINTED\n");

    } else {
        /*
         * Parent process
         */

        printf("Waiting for child process (PID = %d)...\n", pid);

        int ret;
        waitpid(pid, &ret, 0);

        printf("Child exited with status: %d\n", WEXITSTATUS(ret));
    }

    return 0;
}
