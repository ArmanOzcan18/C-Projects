/**
 *  exec-test
 *
 *  This program demonstrates what happens when it recursively exec()s itself.
 *  When called with no arguments, it will exec() itself with an extra argument.
 *
 *  Recall that exec() completely replaces the memory of the caller with that of
 *  a new program.  This behavior has a couple of notable takeaways,
 *  demonstrated by exec-test:
 *
 *    - After calling exec(), the memory of the old program is destroyed,
 *      including any modifications made.  This is true even if the program
 *      exec()s itself; the old, modified instance of the global variable g
 *      is replaced with a new instance of itself, prior to modification.
 *
 *    - The heap of the old program is entirely destroyed upon calling exec()
 *      and replaced with a fresh heap, meaning any memory leaks from the old
 *      process are essentially erased.
 *
 *  By default, Valgrind only works on processes up to the point they call
 *  exec().  However, you can instruct Valgrind to continue tracing the newly
 *  exec()ed process using the (poorly named) --trace-children=yes option.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void die(const char *msg) {
    perror(msg);
    exit(1);
}

// Global variable g is statically initialized to 0.
int g = 0;

int main(int argc, char **argv) {

    if (argc == 1) {

        // We update g to 1, but this modification will be wiped by exec().
        g = 1;

        printf("%s: called with no arguments.\n", argv[0]);
        printf("%s: g = %d\n", argv[0], g);

        // We heap-allocate a string array to store the args we exec() with.
        // Even though we never free() this, the heap (and any leaks within)
        // will be wiped clean by exec().
        char **a = malloc(sizeof(char *) * 3);

        a[0] = argv[0];           // exec() the same program.
        a[1] = "some argument";   // Add an extra argument, doesn't matter what.
        a[2] = NULL;              // NULL-terminate argv like a good citizen.

        printf("%s: calling exec()\n----exec()----\n", argv[0]);

        if (execv(a[0], a) == -1)
            die("execv");

        // UNREACHABLE

        printf("THIS SHOULD NEVER BE PRINTED\n");

    } else {


        printf("%s: called with %d arguments \n", argv[0], argc);
        printf("%s: argv[1] is '%s'\n", argv[0], argv[1]);

        // Now this program has been executed again, g is re-initialized to 0;
        // the modification made before exec() is lost.
        printf("%s: g = %d\n", argv[0], g);

    }

    return 0;
}
