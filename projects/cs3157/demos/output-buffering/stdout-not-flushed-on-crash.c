#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Since stdout is line-buffered, nothing will be printed to the terminal
    // until given a newline.
    fputs("foo...", stdout);

    // So you won't see "foo..." before sleeping:
    sleep(2);

    // If we crash before the program can terminate gracefully, stdout won't be
    // properly flushed.
    return *(int *)NULL;

    // So if your program is trying to write out important data that you don't
    // want to lose in case your program crashes, make sure to fflush()!
}
