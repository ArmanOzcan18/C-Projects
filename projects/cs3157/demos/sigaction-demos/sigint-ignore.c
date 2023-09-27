/**
 *  sigint-ignore
 *
 *  This program configures itself to ignore SIGINT.
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

int main(int argc, char **argv) {

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));         // Zero-initialize sigaction structure
    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_handler = SIG_IGN;            // Ignore the signal

    if (sigaction(SIGINT, &sa, NULL))
        die("sigaction");

    printf("This process (PID = %d) is now ignoring SIGINT.\n", getpid());

    printf("Press ENTER to quit.\n");
    getchar();

    printf("Goodbye!\n");

    return 0;
}
