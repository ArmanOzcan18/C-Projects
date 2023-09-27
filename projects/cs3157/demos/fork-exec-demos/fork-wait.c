/**
 *  fork-wait
 *
 *  A simple program demonstrating a parent using waitpid() to block until its
 *  child terminates.  The parent also reads the child's exit status.
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

        printf("Hello from the child process (PID = %d)\n", getpid());

        // exit(5); // equivalent to returning 5 from main()

        return 5;

    } else {
        /*
         * Parent process
         */

        printf("Hello from the parent process (child PID = %d)\n", pid);

        // Where to write the exit status.
        int ret;

        // If we pass NULL instead of &ret, the exit status will be discarded.
        waitpid(pid, &ret, 0);

        // ret contains more information than the exit status, so we need to use
        // the WEXITSTATUS() macro to read out the exit status code.
        printf("Child exited with status: %d\n", WEXITSTATUS(ret));

        return 0;

    }
}
