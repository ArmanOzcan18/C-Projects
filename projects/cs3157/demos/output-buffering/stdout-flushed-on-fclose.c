#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Since stdout is line-buffered, nothing will be printed to the terminal
    // until given a newline.
    fputs("foo...", stdout);

    // So you won't see "foo..." before sleeping.
    sleep(2);

    // But when we fclose() stdout, we implicitly flush out what is buffered.
    fclose(stdout);

    // Sleep for one more second so that you can distinguish this from
    // stdout-flushed-on-exit.
    sleep(1);

    return 0;
}
