#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {

    if (argc > 2) {
        fprintf(stderr, "%s\n", "usage: myhead [<num-lines>]");
        exit(1);
    }

    // Default to 10 lines
    int lines = 10;

    if (argc == 2) {
        lines = atoi(argv[1]);
    }

    if (lines == 0)
        // Nothing to do.
        return 0;

    char buf[128];
    int l = 1;

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        fputs(buf, stdout);

        // It's possible that a line is greater than 127 characters long, and
        // a call to fgets() didn't finish reading in the line.  So, we only
        // count a line if we read in a newline, which will be right before the
        // null terminator in our buffer.
        if (buf[strlen(buf) - 1] == '\n' && l++ == lines)
            break;
    }

    return 0;
}
