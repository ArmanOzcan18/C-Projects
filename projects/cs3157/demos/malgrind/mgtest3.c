#include <stdio.h>

void *MALLOC(size_t n);
void FREE(void *p);

int main(void) {
    int *a = MALLOC(4 * sizeof(int));

    for (int i = 0; i < 4; i++)
        a[i] = i;

    for (int *p = a - 2; p < a + 6; p++)
        fprintf(stderr, "%d, ", *p);

    FREE(a);

    return 0;
}
