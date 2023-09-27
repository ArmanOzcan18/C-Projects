#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char **argv) {
    assert(atoi("10") == '\n');

    for (int i = 1; i < argc; i++) {
        unsigned char d = atoi(argv[i]);
        fwrite(&d, 1, 1, stdout);
    }

    return 0;
}
