#ifndef _WORDS_H
#define _WORDS_H

#include <stdio.h>
#include <stdlib.h>

#define WORD_SIZE 5

/*
 * Open the file at words_path, and read the pos'th valid word into dest.
 *
 * This function assumes that each word is on its own line, and that each line
 * is less than 32 characters long.
 *
 * Note that this function skips over invalid words, i.e., words longer that
 * aren't exactly 5 characters long and contain characters other than 'a'
 * through 'z'. So if pos is greater than the number of valid words in
 * words_file, this function will fail.
 *
 * Returns 0 on success; non-zero otherwise.
 */
int read_word(char* dest, unsigned int pos, const char* words_path);

/*
 * Count the number of valid words in the file at words_path.
 *
 * Returns -1 if any error is encountered.
 */
int count_words(const char* words_path);

/*
 * Print each valid word in the word file on its own line.
 *
 * Returns 0 on success; non-zero otherwise.
 */
int print_words(const char* words_path);

#endif /* ifndef _WORDS_H */
