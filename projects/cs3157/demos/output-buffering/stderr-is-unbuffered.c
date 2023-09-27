#include <stdio.h>
#include <unistd.h>

int main(void) {
    // Since stderr is unbuffered, you'll see "foo..." printed out immediately.
    fputs("foo...", stderr);

    // We sleep for 2 seconds...
    sleep(2);

    // And then you'll see "bar\n" printed out after we wake up.
    fputs("bar\n", stderr);

    return 0;
}
