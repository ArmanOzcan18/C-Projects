#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Since stdout is line-buffered, nothing will be printed to the terminal
    // until given a newline.
    fputs("foo...", stdout);

    // So you won't see "foo..." before sleeping.
    sleep(2);

    // But when the program quits, stdout will be closed (and thus flushed)
    // implicitly, so we'll still eventually see "foo..." printed out.
    return 0;

    // Note: stdout is also flushed and closed when we exit by calling exit(),
    // e.g.,:
    //
    //    exit(0);
    //
    // or even:
    //
    //    exit(1);
    //
    // Do not confuse crashing with exiting with a non-zero return code!
}
