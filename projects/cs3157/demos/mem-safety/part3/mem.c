#include <stdio.h>
#include <stdlib.h>

int *m(int *n) {
    *n = 0;
    return n;
}

int main(void) {
    int i;
    int *p = m(&i);
    printf("%d\n", *p);
    // p points to i, so trying to free(p) is a memory error.
    // You can only free heap-allocated memory, i.e., pointers from malloc().
    free(p);
    return 0;
}
