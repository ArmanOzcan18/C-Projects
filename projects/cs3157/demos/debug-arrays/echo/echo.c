#include <stdio.h>

int main(int argc, char **argv) {
    argv++;
    while (argv)
        // ^ the bug is here, argv should be dereferenced before being tested,
        // i.e., while(*argv).  Without dereferencing argv, we are not testing
        // whether argv points to a NULL pointer, we are testing whether argv is
        // a NULL pointer (which it isn't, even after being incremented).  This
        // will cause the loop to run more iterations than it should, and feed
        // a NULL pointer to printf(), which will dereference the NULL pointer
        // and segfault.
        printf("%s\n", *argv++);
    return 0;
}

