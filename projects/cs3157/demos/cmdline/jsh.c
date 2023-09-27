/**
 *  jsh
 *
 *  A simple shell implementation.  It reads in commands from stdin and exec()s
 *  them in a child process; the parent waitpid()s until the command terminates
 *  before prompting for another command.  The parent reports any non-zero
 *  exit status it encounters.
 *
 *  This implementation supports the following features:
 *
 *    - tokenize command line into whitespace-separated arguments
 *    - resolving commands using the PATH variable (via execvp())
 *    - builtin exit command to quit
 *    - builtin cd command to change current working directory
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

/** Builtin cd command: changes the current directory of the shell process.
 *
 *  Running cd with no arguments changes the directory to the HOME directory.
 *
 *  Note that this needs to be a builtin because it doesn't make any sense to
 *  run this as a child; the CWD is a property of each process, so changing the
 *  CWD of the child won't affect that of the parent.
 */
static void do_cd(char **argv) {
    size_t len = argv_len(argv);
    if (len > 2) {
        fprintf(stderr, "jsh: cd: too many arguments.\n");
        return;
    }

    // Obtain HOME directory from environment using getenv().
    if (chdir(len == 2 ? argv[1] : getenv("HOME")) == -1)
        perror("jsh: cd");
}

int main(void) {
    char buf[4097];

    put_prompt("$ ");
    while (fgets(buf, sizeof(buf), stdin)) {
        if (cmd_empty(buf))
            goto next_prompt;

        if (cmd_matches(buf, "exit"))
            break;

        if (cmd_matches(buf, "cd")) {
            char **argv = make_argv(buf);
            do_cd(argv);
            free(argv);
            goto next_prompt;
        }

        pid_t pid = fork();
        if (pid == -1)
            die("fork");

        if (pid == 0) {
            /*
             * Child: exec() command.
             */
            char **argv = make_argv(buf);

            execvp(argv[0], argv);

            // UNREACHABLE
            die("exec");
        }

        /*
         * Parent: wait() for child.
         */
        int wstatus;
        waitpid(pid, &wstatus, 0);
        log_wstatus(trim_whitespace(buf), wstatus);

next_prompt:
        put_prompt("$ ");
    }

    // If user pressed Ctrl-D, print "exit" for prettier termination output.
    if (feof(stdin))
        fputs("exit\n", stdout);

    return 0;
}
