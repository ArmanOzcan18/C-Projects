/**
 *  jsh-io
 *
 *  A toy shell implementation, which supports the following features:
 *
 *    - tokenize command line into whitespace-separated arguments
 *    - builtin exit command to quit
 *    - builtin cd command to change current working directory
 *    - resolving the PATH variable
 *    - piping (e.g., yes | head)
 *    - file redirection (e.g., grep foo < bar > baz)
 *
 *  Pipes and redirection are quite gnarly to get right.  If you're reading this
 *  and are wondering how this works, ask John at OHs or on the listserv!
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

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


/** Execute a command, with file redirection. */
static void do_exec(char *cmd) {
    if (cmd_matches(cmd, "exit") || cmd_matches(cmd, "cd"))
        // Don't bother exec()ing for built-ins
        exit(0);

    char **argv = make_argv(cmd);

    /*
     * We need to parse for the '<', '>', and '>>' redirection operators.
     *
     * Note that this quick and dirty implementation supports both "cmd >file"
     * and "cmd > file" syntax but not "cmd>file".
     */

    for (int i = 0; argv[i]; i++) {
        if (argv[i][0] == '<' || argv[i][0] == '>') {
            // We're looking at a redirection operator. Look for these.
            char *pathname, *op;
            int flags, offset;

            // Determine flags
            if (argv[i][0] == '<')
                op = "<", flags = O_RDONLY;
            else if (argv[i][1] == '>')
                op = ">>", flags = O_CREAT | O_WRONLY | O_APPEND;
            else
                op = ">", flags = O_CREAT | O_WRONLY | O_TRUNC;

            // Determine pathname and offset
            if (argv[i][1] && argv[i][1] != '>')
                pathname = argv[i] + 1, offset = 1;
            else if (argv[i][1] == '>' && argv[i][2])
                pathname = argv[i] + 2, offset = 1;
            else if (argv[i + 1] == NULL)
                fprintf(stderr, "Syntax error: '%s' must be followed by path.\n", op), exit(1);
            else
                pathname = argv[i + 1], offset = 2;

            int fd = open(pathname, flags, S_IRWXU | S_IRWXG | S_IRWXO);
            if (fd < 0)
                die(pathname);
            dup2(fd, argv[i][0] == '<' ? 0 : 1);

            // Shift rest of arguments over by offset.
            for (int j = 0; argv[i + j]; j++)
                argv[i + j] = argv[i + j + offset];

            // Now that we've shifted everything over, parse this again.
            i--;
        }
    }

    /*
     * The parent ignores SIGINT, and we've inherited that disposition as the
     * child process.  We need to restore it before executing another program.
     */

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));         // Zero-initialize sigaction structure
    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_handler = SIG_DFL;            // Restore default signal handler
    sigaction(SIGINT, &sa, NULL);

    execvp(argv[0], argv);
    die("exec");
}

/** Execute a pipeline of commands.
 *
 *  The stdout of each previous program is connected to the stdin of the next,
 *  using a pipe().
 */
static void do_pipe(char *line) {
    int children = 0, in_fd = 0;
    char *cmd, *cmd2 = strtok(line, "|");
    while (cmd = cmd2, cmd2 = strtok(NULL, "|")) {
        int pfd[2];
        if (pipe(pfd) < 0)
            die("pipe");

        children++;
        pid_t pid = fork();
        if (pid == -1)
            die("fork");

        if (pid == 0) {
            // Child
            dup2(in_fd, 0), dup2(pfd[1], 1);
            close(pfd[0]), close(pfd[1]), close(in_fd);
            do_exec(cmd);
        }

        // Parent
        if (in_fd) // Only close in_fd if it's not stdin
            close(in_fd);
        close(pfd[1]);
        in_fd = pfd[0];
    }

    children++;
    pid_t pid = fork();
    if (pid == -1)
        die("fork");

    if (pid == 0) {
        // Child
        dup2(in_fd, 0);
        close(in_fd);
        do_exec(cmd);
    }

    // Parent
    if (in_fd) // Only close in_fd if it's not stdin
        close(in_fd);

    // Block until entire pipeline has terminated
    while (children--)
        waitpid(-1, NULL, 0);

    // TODO: idk log wstatus or something
}

int main(void) {
    // Ignore SIGINT
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));         // Zero-initialize sigaction structure
    sigemptyset(&sa.sa_mask);           // Don't mask any signals
    sa.sa_handler = SIG_IGN;            // Ignore the signal
    sigaction(SIGINT, &sa, NULL);

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

        if (strchr(buf, '|')) {
            do_pipe(buf);
            goto next_prompt;
        }

        pid_t pid = fork();
        if (pid == -1)
            die("fork");

        if (pid == 0)
            do_exec(buf);

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
