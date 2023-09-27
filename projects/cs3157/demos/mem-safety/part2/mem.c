#include <stdio.h>
#include <stdlib.h>

int g;

int *m(int n) {
    // There's nothing wrong with returning an address to a global variable,
    // since it is never deallocated.
    g = n;
    return &g;
}

int main(void) {
    int *p = m(1);
    printf("%d\n", *p);
    // No need to free a pointer to a global variable either.
    return 0;
}
