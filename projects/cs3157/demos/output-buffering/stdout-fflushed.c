#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Since stdout is line-buffered, nothing will be printed to the terminal
    // until given a newline.
    fputs("foo...", stdout);

    // But we can force stdout "foo..." to be printed immediately using fflush()
    fflush(stdout);

    // So you'll see "foo..." before sleeping for 2 seconds...
    sleep(2);

    // Followed by "bar\n".
    fputs("bar\n", stdout);

    return 0;
}
