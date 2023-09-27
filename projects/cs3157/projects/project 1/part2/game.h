#ifndef _GAME_H
#define _GAME_H

#include <stddef.h>

/*
 * Play wordle, with some pre-determined answer and number of guesses.
 *
 * The answer should be a valid word, i.e., it should be exactly WORD_SIZE
 * characters long and only contain lowercase letters.
 *
 * If max_guesses is negative, the game will not limit the number of guesses.
 */
void play_game(const char* answer, int max_guesses);

#endif /* ifndef _GAME_H */
