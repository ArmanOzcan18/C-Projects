/**
 *  sigchld-handler
 *
 *  This program configures itself to automatically reap terminated children
 *  upon receiving SIGCHLD.
 *
 *  Try commenting out the SA_RESTART option to see how blocking system calls
 *  behave without it.  Relevant blocking system calls include read() and
 *  accept().
 */

// _GNU_SOURCE is needed for sigaction().
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

void sigint_handler(int sig) {
    printf("Child terminated! Reaping it now...\n");
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

int main(int argc, char **argv) {

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));         // Zero-initialize sigaction structure
    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_flags = SA_RESTART;           // Restart interrupted system calls
    sa.sa_handler = &sigint_handler;    // Handle the signal

    if (sigaction(SIGCHLD, &sa, NULL))
        die("sigaction");

    if (fork() == 0) {
        printf("    Child 1 is going to sleep for 1 second...\n");
        sleep(1);
        printf("    Child is about to exit. Goodbye!\n");
        exit(0);
    }

    if (fork() == 0) {
        printf("        Child 2 is going to sleep for 2 seconds...\n");
        sleep(2);
        printf("        Child is about to exit. Goodbye!\n");
        exit(0);
    }

    printf("Parent will now block and wait for input from stdin.\n");

    printf("Press ENTER to quit.\n");

    // Block, reading from stdin (fd = 0)
    char c;
    read(0, &c, sizeof(c));

    // Note that if we didn't specify .sa_flags = SA_RESTART earlier,
    // SIGCHLD would case read() to unblock after the signal is handled.

    printf("Parent is about to exit. Goodbye!\n");

    return 0;
}
