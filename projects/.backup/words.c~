#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "words.h"

/*
 * Helper function to determine whether the given string is a valid word.
 *
 * Returns 0 if word is invalid, 1 if valid.
 */
int valid_word(const char* word)
{
    int len = strlen(word);

    if (len != WORD_SIZE)
        return 0;

    for (int i = 0; i < len; i++)
        if (word[i] < 'a' || word[i] > 'z')
            return 0;

    return 1;
}

int read_word(char* dest, unsigned int pos, const char* words_path)
{
    // Open file containing words.
    FILE* words_file = fopen(words_path, "rb");

    // Could not open file; report error by returning -1.
    if (words_file == NULL)
        return -1;

    int count = 0; // Keep count of how many valid words we have encountered.
    char word_buf[32]; // Assume no word is longer than 32 characters.

    // Each word is on its own line. Read each word into word_buf.
    while (fgets(word_buf, sizeof(word_buf), words_file) > 0) {

        // At this point, word contains a newline. Trim it out:
        word_buf[strlen(word_buf) - 1] = '\0';

        if (valid_word(word_buf)) {
            if (count == pos) {
                // Copy the word into the count-th position to destination.
                strncpy(dest, word_buf, strlen(word_buf));

                // Done reading from the words file, so let's close it.
                fclose(words_file);

                // Indicate success by returning 0.
                return 0;
            }
            count++;
        }
    }

    // Done reading from the words file, so let's close it.
    fclose(words_file);

    // Did not end up finding any words, so report error by returning -1.
    return -1;
}

/*
 * Count the number of valid words in the file at words_path.
 *
 * Returns -1 if any error is encountered.
 */
int count_words(const char* words_path)
{
    // Open file containing words.
    FILE* words_file = fopen(words_path, "rb");

    // Could not open file; report error by returning -1.
    if (words_file == NULL)
	return -1;
	
    int count = 0; // Keep count of how many valid words we have encountered.
    char word_buf[32]; // Assume no word is longer than 32 characters.

    // Each word is on its own line. Read each word into word_buf.
    while (fgets(word_buf, sizeof(word_buf), words_file) > 0) {

        // At this point, word contains a newline. Trim it out:
        word_buf[strlen(word_buf) - 1] = '\0';

        if (valid_word(word_buf)) {
            count++;
	}

    }

    // Done reading from the words file, so let's close it.
    fclose(words_file);

    // Return the number of words encountered.
    return count;
  
}

/*
 * Print each valid word in the word file on its own line.
 *
 * Returns 0 on success; non-zero otherwise.
 */
int print_words(const char* words_path)
{
    // Open file containing words.
    FILE* words_file = fopen(words_path, "rb");

    // Could not open file; report error by returning -1.
    if (words_file == NULL)
        return -1;

    char word_buf[32]; // Assume no word is longer than 32 characters.

    // Each word is on its own line. Read each word into word_buf.
    while (fgets(word_buf, sizeof(word_buf), words_file) > 0) {
	
	// At this point, word contains a newline. Trim it out:
        word_buf[strlen(word_buf) - 1] = '\0';
        
	if (valid_word(word_buf)) {
	    //Print the word
	    printf("%s\n",word_buf);
        }
    }

    // Done reading from the words file, so let's close it.
    fclose(words_file);

    // Successfully printed any valid words in the file, so return 0
    return 0;
}
