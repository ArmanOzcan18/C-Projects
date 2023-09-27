#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    /*
     * Parse arguments
     */

    if (argc > 2) {
        fprintf(stderr, "%s\n", "usage: myhead [<num-lines>]");
        exit(1);
    }

    // Default to 10 lines
    int lines = 10;

    if (argc == 2) {
        lines = atoi(argv[1]);
    }

    /*
     * YOUR SOLUTION HERE
     */

    return 0;
}
