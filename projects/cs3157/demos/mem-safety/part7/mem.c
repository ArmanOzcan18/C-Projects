#include <stdio.h>
#include <stdlib.h>

int *m(int *n) {
    // We assume n is non-NULL (according to the prompt), so we go to *n = 1 and
    // successfully initialize our heap-allocated pointer.
    if (n)
        *n = 1;
    return n;
}

int main(void) {
    // Looks tricky, but realize that sizeof does not evaluate its argument,
    // so sizeof(m(NULL)) is just the size of the return type of calling m().
    // This is the same as writing m(malloc(sizeof(int *))), or m(malloc(8)).
    int *p = m(malloc(sizeof(m(NULL))));
    printf("%d\n", *p);
    // We didn't free() p.  Oopsies xD
    return 0;
}
