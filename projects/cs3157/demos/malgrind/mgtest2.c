#include <stdio.h>
#include <assert.h>

void *MALLOC(size_t n);
void FREE(void *p);

int main(void) {
    assert(sizeof(long) == sizeof(void *));

    long *a = MALLOC(4 * sizeof(long));

    for (long i = 0; i < 4; i++)
        a[i] = i;

    for (long *p = a; *p >= 0; p++)
        fprintf(stderr, "%ld, ", p[1]);

    FREE((void *) *a);

    return 0;
}
