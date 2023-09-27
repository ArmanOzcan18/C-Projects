#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Since stdout is line-buffered, nothing will be printed to the terminal
    // until given a newline.
    fputs("foo...", stdout);

    // So you won't see "foo..." before sleeping:
    sleep(2);

    // You'll only see "foo..." when it gets printed out alongside "bar\n", due
    // to the newline.
    fputs("bar\n", stdout);

    return 0;
}
