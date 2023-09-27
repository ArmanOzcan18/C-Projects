/**
 *  jsh-basic
 *
 *  A basic shell implementation.  It reads in commands from stdin and exec()s
 *  them in a child process; the parent waitpid()s until the command terminates
 *  before prompting for another command.  The parent reports any non-zero
 *  exit status it encounters.
 *
 *  This basic implementation doesn't support passing arguments to commands, nor
 *  does it support builtin commands like cd or exit.  For those features, see
 *  jsh.
 *
 *  Note that this implementation requires the full path to each executable,
 *  e.g.:
 *
 *      $ /usr/bin/ls
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "cmdline.h"

/** Print out the shell prompt to stdout (with fflush()). */
static void put_prompt(const char *prompt) {
    fputs(prompt, stdout);
    fflush(stdout);
}

/** Report any exception termination (e.g., non-zero exit status code.) */
static void log_wstatus(const char *cmd_line, int wstatus) {
    if (!WIFEXITED(wstatus)) {
        fprintf(stderr, "jsh: Command did not terminate normally: %s\n",
                cmd_line);
        return;
    }
    if (WEXITSTATUS(wstatus) != 0) {
        fprintf(stderr, "jsh: Non-zero exit status(%d): %s\n",
                WEXITSTATUS(wstatus),
                cmd_line);
        return;
    }
}

int main(void) {
    char buf[4097];

    put_prompt("$ ");
    while (fgets(buf, sizeof(buf), stdin)) {

        if (cmd_empty(buf))
            goto next_prompt;

        // Get rid of any leading and trailing whitespace (e.g., trailing '\n').
        char *cmd_line = trim_whitespace(buf);

        pid_t pid = fork();
        if (pid == -1)
            die("fork");

        if (pid == 0) {
            /*
             * Child: exec() command.
             */
            char *argv[] = {cmd_line, NULL};
            execv(*argv, argv);

            // UNREACHABLE
            die("exec");
        }

        /*
         * Parent: wait() for child.
         */
        int wstatus;
        waitpid(pid, &wstatus, 0);
        log_wstatus(cmd_line, wstatus);

next_prompt:
        put_prompt("$ ");
    }

    // Print "exit" for prettier termination output.
    fputs("exit\n", stdout);

    return 0;
}
