#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdline.h"

/** Returns non-zero for ' ', '\t', '\r', and '\n'; returns zero otherwise. */
static int is_whitespace(char c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}


void die(const char *msg) {
    perror(msg);
    exit(1);
}

int cmd_empty(const char *cmd_line) {
    while (*cmd_line)
      if (!is_whitespace(*cmd_line++))
          return 0;
    return 1;
}

int cmd_matches(const char *cmd_line, const char *cmd) {
    while (*cmd_line && is_whitespace(*cmd_line))
        cmd_line++;
    while (*cmd_line && *cmd)
        if (*cmd_line++ != *cmd++)
            return 0;;
    return *cmd_line && is_whitespace(*cmd_line);
}

char *trim_whitespace(char *cmd_line) {
    while (*cmd_line && is_whitespace(*cmd_line))
        cmd_line++;
    char *s = cmd_line + strlen(cmd_line);
    while (cmd_line < s-- && is_whitespace(*s))
        *s = '\0';
    return cmd_line;
}

size_t argv_len(char **argv) {
    size_t len = 0;
    while (*argv++)
        len++;
    return len;
}

char **make_argv(char *cmd_line) {
    int line_len = strlen(cmd_line);
    int argc = 0;

    /*
     * Scan through cmd_line, converting whitespace into null bytes and
     * counting the number of argumentss separated by that whitespace.
     *
     * Implemented as a simple state machine (a Mealy machine) with two states:
     * one for scanning whitespace and the other for scanning non-whitespace
     * (i.e., arguments).
     */
    for (int i = 0, scanning_whitespace = 1; i < line_len; i++) {
        if (scanning_whitespace) {
            if (is_whitespace(cmd_line[i])) {
                // Still scanning whitespace; convert it to a null byte.
                cmd_line[i] = '\0';
            } else {
                // Encountered first character of an arg! Increment argc and
                // transition state.
                argc++;
                scanning_whitespace = 0;
            }
        } else {
            if (is_whitespace(cmd_line[i])) {
                // Encountered first whitespace after an argument! Convert it to
                // a null byte and transition state.
                cmd_line[i] = '\0';
                scanning_whitespace = 1;
            } else {
                // Still scanning an argument; do nothing.
            }
        }
    }

    /*
     * Allocate argv, with 1 extra space for the NULL-pointer terminator.
     */

    char **argv = malloc((argc + 1) * sizeof(char *));

    /*
     * Assign each word in cmd_line to argv.
     */
    for (int i = 0; i < argc; i++) {
        // Scan to first character of next word.
        while (*cmd_line == '\0')
            cmd_line++;

        // Assign word to argv.
        argv[i] = cmd_line;

        // Scan to end of word.
        while (*cmd_line != '\0')
            cmd_line++;
    }

    // Add NULL-pointer terminator to argv.
    argv[argc] = NULL;

    return argv;
}
