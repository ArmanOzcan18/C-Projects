#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game.h"
#include "words.h"

/*
 * Enumerated constants representing the different actions this program can
 * perform.
 */
#define ACTION_HELP 1
#define ACTION_PLAY 2
#define ACTION_SHOW 3
#define ACTION_DUMP 4

/*
 * The following global variables are set while parsing arguments, and control
 * what the program does afterwards. They are initialized to default values.
 */
int action = ACTION_PLAY; // What action to perform
const char* words_path = NULL; // Path of file to read words from
long word_number = -1; // Which word to pick from words_path file
size_t max_guesses = 5; // Maximum number of guesses the user may make
char word[WORD_SIZE + 1]; // What word is picked

/*
 * If the program encounters any errors while parsing arguments, it will set
 * error_msg (and optionally error_msg2) to in indicate what the error was.
 * These will be printed in the main() function.
 */
const char* error_msg = NULL;
const char* error_msg2 = NULL;

/*
 * Returns non-zero if the argument matches the target; zero otherwise.
 */
int match_arg(const char* arg, const char* target)
{
    return strcmp(arg, target) == 0;
}

/*
 * Returns non-zero if the argument matches either short_flag or long_flag;
 * returns zero otherwise.
 */
int match_flag(const char* arg, const char* short_flag, const char* long_flag)
{
    return match_arg(arg, short_flag) || match_arg(arg, long_flag);
}

/*
 * Parses arg as a non-negative integer; returns negative integer upon error.
 */
int parse_positive_number(const char* arg)
{
    int number = atoi(arg);

    if (word_number == 0 && !match_arg(arg, "0"))
        return -1; // Return arbitrary negative number

    return number;
}

/*
 * Helper function to parse arguments, setting global variables accordingly.
 */
void parse_args(int argc, char** argv)
{
    // This variable indicates whether we are parsing options (0) or actions (1).
    // If it is greater than 1, then we are done parsing actions, so we
    int parsing_action = 0;

    for (size_t i = 1; i < argc; i++) {
        if (parsing_action > 1) {
            // Too many arguments
            error_msg = "Too many arguments; only one action supported at a time";
            return;
        }

        if (argv[i][0] == '-' && parsing_action == 0) {
            // We are parsing an option (i.e., something that begins with '-').

            if (match_arg(argv[i], "--")) {

                parsing_action = 1;

            } else if (match_flag(argv[i], "-h", "--help")) {

                action = ACTION_HELP;

                // If -h/--help is specified, none of the other arguments matter,
                // so we don't even bother parsing anything else.
                return;

            } else if (match_flag(argv[i], "-f", "--file")) {

                if (++i >= argc) {
                    error_msg = "-f/--file must be followed by file path";
                    return;
                }

                words_path = argv[i];

            } else if (match_flag(argv[i], "-g", "--guesses")) {

                if (++i >= argc) {
                    error_msg = "-g/--guesses must be followed by a number";
                    return;
                }

                if (match_arg(argv[i], "-")) {
                    max_guesses = -1;
                } else {
                    max_guesses = parse_positive_number(argv[i]);

                    if (max_guesses < 0) {
                        error_msg = "Could not parse argument for -g/--guesses";
                        error_msg2 = argv[i];
                        return;
                    }
                }
            } else if (match_flag(argv[i], "-n", "--number")) {

                if (++i >= argc) {
                    error_msg = "-n/--number must be followed by a number";
                    return;
                }

                if (match_arg(argv[i], "-")) {
                    word_number = -1;
                } else {
                    word_number = parse_positive_number(argv[i]);

                    if (word_number < 0) {
                        error_msg = "Could not parse argument for -n/--number";
                        error_msg2 = argv[i];
                        return;
                    }
                }
            } else {
                error_msg = "Unrecognized flag";
                error_msg2 = argv[i];
                return;
            }
        } else {
            // We are (or at least should be) parsing an action.
            parsing_action = 2;

            if (match_arg(argv[i], "play")) {
                action = ACTION_PLAY;
            } else if (match_arg(argv[i], "show")) {
                action = ACTION_SHOW;
            } else if (match_arg(argv[i], "dump")) {
                action = ACTION_DUMP;
            } else {
                error_msg = "Unrecognized argument";
                error_msg2 = argv[i];
            }
        }
    }
}

/*
 * Helper function to print the help documentation for this program.
 */
void show_usage(const char* exec_name)
{
    fprintf(stderr, "Usage:\n");
    fprintf(stderr, "    %s [<options>] [--] <action>\n", exec_name);
    fprintf(stderr, "\n");
    fprintf(stderr, "OPTIONS\n");
    fprintf(stderr, "    -h, --help          show this help menu\n");
    fprintf(stderr, "    -f, --file          path to word file\n");
    fprintf(stderr, "    -n, --number NUM    choose the NUMth valid word;\n");
    fprintf(stderr, "                        use '-' to choose a random word\n");
    fprintf(stderr, "                        (default: -)\n");
    fprintf(stderr, "    -g, --guesses NUM   allow maximum NUM guesses;\n");
    fprintf(stderr, "                        use '-' for unlimited guesses\n");
    fprintf(stderr, "                        (default: 5)\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "ACTIONS\n");
    fprintf(stderr, "    play    play word guessing game\n");
    fprintf(stderr, "    show    print chosen word\n");
    fprintf(stderr, "    dump    print all words in word file\n");
    fprintf(stderr, "\n");
}

/*
 * Helper function to pick a possibly random word, depending on word_number.
 */
int pick_word(void)
{
    int num_words = count_words(words_path);

    if (num_words <= 0)
        return 1;

    if (word_number >= num_words)
        return 1;

    if (word_number < 0) {
        // Pick random word
        srandom(time(NULL));
        word_number = random() % num_words;
    }

    return read_word(word, word_number, words_path);
}

/*
 * Entry point of the program.
 *
 * When the user runs ./wordle from the command line, the program starts here,
 * with argc set to the number of the arguments, and argv pointing to the array
 * of arguments.
 */
int main(int argc, char** argv)
{
    parse_args(argc, argv);

    if (error_msg) {
        if (error_msg2) {
            fprintf(stderr, "Error: %s: %s\n\n", error_msg, error_msg2);
        } else {
            fprintf(stderr, "Error: %s\n\n", error_msg);
        }
        show_usage(argv[0]);
        return 1;
    }

    if (action == ACTION_HELP) {
        show_usage(argv[0]);
        return 0;
    }

    if (words_path == NULL) {
        fprintf(stderr,
            "Error: words file must be specified using -f/--file flag\n\n");
        show_usage(argv[0]);
        return 1;
    }

    if (action == ACTION_PLAY) {

        if (pick_word()) {
            fprintf(stderr, "Error: could not find valid word in file: %s\n",
                words_path);
            return 1;
        }

        play_game(word, max_guesses);

        return 0;

    } else if (action == ACTION_SHOW) {

        if (pick_word()) {
            fprintf(stderr, "Error: could not find valid word in file: %s\n",
                words_path);
            return 1;
        }

        printf("Word at position %ld: %s\n", word_number, word);

        return 0;

    } else if (action == ACTION_DUMP) {

        if (print_words(words_path) != 0) {
            fprintf(stderr, "Error: could not read from words file: %s\n",
                words_path);
            return 1;
        }

        printf("Found %d words\n", count_words(words_path));
        return 0;
    }
}
