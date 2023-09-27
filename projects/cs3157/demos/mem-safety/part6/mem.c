#include <stdio.h>
#include <stdlib.h>

int *m(int n) {
    int *p = malloc(n);
    *p = n;
    return p;
}

int main(void) {
    int *p = m(sizeof(int));
    printf("%d\n", *p);
    free(p);
    free(p); // Double-free() is a memory error!
    // Rule of thumb: each malloc() should be matched with exactly one free().
    return 0;
}
