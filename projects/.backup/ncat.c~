/*
 * ncat <file-name>
 *
 * Print the contents of a file with line numbers, to stdout.
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    /*
     * Open file whose name is given by argv[1].
     */

    if (argc != 2) {
        fprintf(stderr, "%s\n", "usage: ncat <file-name>");
        exit(1);
    }

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror(filename);
        exit(1);
    }


    /*
     * Read the file line-by-line, printing out line numbers as we go.
     */

    // Define a buffer we will read each line into.
    char buf[128];
    int lineno = 1;

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        printf("[%4d]", lineno++);
        fputs(buf, stdout);

        // There's a bug here. Can you think of what it might be?
    }

    /*
     * Did we terminate the fgets() loop because of an error?
     * If so, report the error.
     */

    if (ferror(fp)) {
        perror(filename);
        exit(1);
    }

    /*
     * Close our file pointer, and quit.
     */

    fclose(fp);
    return 0;
}
