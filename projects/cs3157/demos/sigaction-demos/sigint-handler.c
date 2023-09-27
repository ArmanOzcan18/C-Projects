/**
 *  sigint-handler
 *
 *  This program configures itself to handle SIGINT with a handler function.
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

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

void sigint_handler(int sig) {
    printf("SIGINT received!\n");

    // You can still terminate the program upon receiving SIGINT, to mimick the
    // default SIGINT behavior.
    // exit(1);
}

int main(int argc, char **argv) {

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));         // Zero-initialize sigaction structure
    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_flags = SA_RESTART;           // Restart interrupted system calls
    sa.sa_handler = &sigint_handler;    // Handle the signal

    if (sigaction(SIGINT, &sa, NULL))
        die("sigaction");

    printf("This process (PID = %d) is now handling SIGINT.\n", getpid());
    printf("Press Ctrl-C to invoke signal handler.\n");

    printf("Press ENTER to quit.\n");

    // Block, reading from stdin (fd = 0)
    char c;
    read(0, &c, sizeof(c));

    // Note that if we didn't specify .sa_flags = SA_RESTART earlier,
    // SIGINT would case read() to unblock after the signal is handled.

    printf("Goodbye!\n");

    return 0;
}
