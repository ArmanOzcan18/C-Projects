#include <stdio.h>
#include <unistd.h>

int main(void) {
    fputs("Note: This program will hang indefinitely, with buffered stdout.\n", stderr);
    fputs("Press Ctrl-C to kill it.\n", stderr);

    // Since stdout is line-buffered, nothing will be printed to the terminal
    // until given a newline.
    fputs("foo...", stdout);

    // This hangs the program indefinitely (for our purposes); we can kill the
    // program using Ctrl-C, but then we will never see "foo..." printed out.
    pause();

    return 0;
}
