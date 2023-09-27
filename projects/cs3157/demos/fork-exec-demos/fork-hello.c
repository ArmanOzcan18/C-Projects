/**
 *  fork-hello
 *
 *  A simple program that demonstrates the basic behavior of fork().  The parent
 *  and child no longer share any memory, so neither's copy of i nor g will be
 *  incremented.
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

// Some global variable.
int g = 0;

int main(void) {

    // Some local variable.
    int i = 0;

    pid_t pid = fork();
    if (pid < 0)
        die("fork");

    // From this point on, BOTH the child and parent processa are executing this
    // program, with the only difference being the value of the pid variable.

    if (pid == 0) {
        /*
         * Child process
         */

        // In the child process, pid is 0 (not the PID of any actual process)

        printf("Hello from the child process (PID = %d)\n", getpid());

    } else {
        /*
         * Parent process
         */

        // In the parent process, pid is the PID of its newly spawned child.

        printf("Hello from the parent process (child PID = %d)\n", pid);

    }

    // After executing their respective halves of the previous conditional
    // statement, BOTH the parent and child will execute the following print
    // statement.  Note that since they do not share any memory, modifications
    // by one process to either i or g will not be seen by the other.

    printf("Both say hello! i = %d, g = %d\n", i++, g++);

    return 0;
}
