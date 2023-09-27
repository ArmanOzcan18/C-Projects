#include <stdio.h>
#include <stdlib.h>

int *m(int n) {
    int *p = malloc(n);
    *p = n;
    free(p);
    return p;
}

int main(void) {
    int *p = m(sizeof(int));
    // p is a dangling pointer, but reading the pointer value p is OK as long as
    // we do not dereference it (-:
    printf("%p\n", (void *)p);
    return 0;
}

