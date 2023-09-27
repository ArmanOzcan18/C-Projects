/**
 *  cmdline.h
 *
 *  A small collection of common command-line parsing and handling utilities.
 *
 *  Whitespace is defined as ' ', '\t', '\r', or '\n'.
 */
#ifndef __CMDLINE_H
#define __CMDLINE_H

/** Print out the reason code assigned to errno, and then exit(1). */
void die(const char *msg);

/** Tests whether cmd_line consists of only whitespace. */
int cmd_empty(const char *cmd_line);

/** Tests whether cmd_line begins with cmd. */
int cmd_matches(const char *cmd_line, const char *cmd);

/** Trims whitespace from either end of cmd_line.
 *
 *  Modifies cmd_line in-place, and returns a pointer to the first
 *  non-whitespace character within cmd_line (if any).
 */
char *trim_whitespace(char *cmd_line);

/** Returns number of strings that a NULL-terminated argv points to. */
size_t argv_len(char **argv);

/** Constructs a heap-allocated argv out of cmd_line.
 *
 *  Works kind of like strtok() (except this doesn't rely on global state):
 *  cmd_line is modified in-place with all whitespace replaced by null bytes;
 *  the returned argv contains pointers to each word within the cmd_line buffer.
 *
 *  Note that this function uses a very, very primitive tokenization algorithm.
 *  It doesn't support quotes (e.g., "'foo bar'" is considered two tokens,
 *  "'foo" and "bar'"), nor does it recognize pipes (e.g., "foo|bar" is
 *  considered a single token).
 *
 *  The returned value should be free()d (or trashed with exec()) to avoid
 *  memory leaks.
 */
char **make_argv(char *cmd_line);

#endif
