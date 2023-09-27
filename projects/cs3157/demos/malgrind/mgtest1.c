#include <stdio.h>

void *MALLOC(size_t n);
void FREE(void *p);

int main(void) {
    int *a = MALLOC(4 * sizeof(int));

    for (int i = 0; i < 5; i++)
        a[i] = i;

    for (int i = 0; i < 5; i++)
        fprintf(stderr, "%d, ", a[i]);

    FREE(a);

    return 0;
}
