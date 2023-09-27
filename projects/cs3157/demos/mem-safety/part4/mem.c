#include <stdio.h>
#include <stdlib.h>

int *m(int n) {
    return malloc(n);
}

int main(void) {
    int *p = m(sizeof(int));
    // p points to uninitialized heap memory.
    // Reading that heap memory causes memory errors.
    printf("%d\n", *p);
    free(p);
    return 0;
}
