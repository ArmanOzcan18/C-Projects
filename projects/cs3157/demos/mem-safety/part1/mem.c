#include <stdio.h>
#include <stdlib.h>

int *m(int n) {
    // n is stack-allocated, so returning &n creates a dangling pointer!
    return &n;
}

int main(void) {
    int *p = m(1);
    printf("%d\n", *p);
    return 0;
}
