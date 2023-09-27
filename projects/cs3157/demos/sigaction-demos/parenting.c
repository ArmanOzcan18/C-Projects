/**
 *  parenting
 *
 *  A "shell" that prompts for sleep times, and spawns child processes that
 *  sleep for the specified amount of time.
 *
 *  Reaps those child processes using a SIGCHLD handler that calls waitpid() in
 *  a non-blocking loop.
 */

// _GNU_SOURCE is needed for sigaction().
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void die(const char *msg) {
    perror(msg);
    exit(1);
}


/** Print out the shell prompt to stdout (with fflush()). */
static void put_prompt(void) {
    fputs("Sleep time: ", stdout);
    fflush(stdout);
}

/** Parse user input and translate it to sleep_time; return 0 on error. */
static int parse_sleep_time(char *buf) {
    // No child should sleep this much anyway.
    if (strlen(buf) > 10) {
        fprintf(stderr, "Invalid sleep time: %s\n", buf);
        return 0;
    }

    // Chop off newline.
    buf[strlen(buf) - 1] = '\0';

    // Empty input?
    if (strlen(buf) == 0)
        return 0;

    int sleep_time = atoi(buf);

    if (sleep_time == 0) {
        fprintf(stderr, "Invalid sleep time: %s\n", buf);
        return 0;
    }

    if (sleep_time > 10) {
        fprintf(stderr, "Children will only sleep <10 seconds.\n");
        return 0;
    }

    return sleep_time;
}

/** Signal handler for SIGCHLD, to promptly reap zombies. */
static void sigchld_handler(int sig)
{
    // Add newline to pending prompt.
    fputs("\n", stdout);

    // Keep reaping zombie children until there aren't any to reap.  Note that
    // we use WNOHANG here because we don't want to block if there are
    // still-running children; we only care about reaping the terminated ones.
    pid_t pid;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        fprintf(stderr, "Child (PID = %d) terminated and reaped.\n", pid);

    // Prompt for port number again.
    put_prompt();
}

int main(void) {
    /*
     * Install a handler for the SIGCHLD signal to reap zombie children.
     */

    // Define and zero-initialize sigaction structure before configuring it.
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    // We don't care about blocking signals in the signal handler.
    sigemptyset(&sa.sa_mask);

    // We don't want SIGCHLD to interrupt certain syscalls (e.g., read()).
    sa.sa_flags = SA_RESTART;

    // Specify sigchld_handler() as the handler.
    sa.sa_handler = &sigchld_handler;

    // Register new signal disposition for SIGCHLD, which is sent to the parent
    // when a child terminates.
    if (sigaction(SIGCHLD, &sa, NULL))
        die("sigaction(SIGCHLD)");

    /*
     * Prompt loop for port numbers.
     */

    char buf[32];

    put_prompt();
    while (fgets(buf, sizeof(buf), stdin)) {

        int sleep_time = parse_sleep_time(buf);
        if (sleep_time == 0)
            goto next_prompt;

        fprintf(stderr, "Making child sleep for %d seconds...\n", sleep_time);

        pid_t pid = fork();
        if (pid == -1)
            die("fork");

        if (pid == 0) {
            /*
             * Child: sleep for some time and terminate.
             */
            fprintf(stderr, "\n(%d) I'm going to sleep now.\n", getpid());
            sleep(sleep_time);
            fprintf(stderr, "\n(%d) Waaaahhh I'm awake now.\n", getpid());
            exit(0);
        }

        /*
         * Parent: just let child sleep while waiting to make new children.
         */

next_prompt:
        put_prompt();
    }

    fputs("\n", stdout);

    // Note that at this point, there may still be running children;
    // when the parent terminates, those children will be come orphans.
    // However, they will be adopted by init and promptly reaped when they exit.

    return 0;
}
