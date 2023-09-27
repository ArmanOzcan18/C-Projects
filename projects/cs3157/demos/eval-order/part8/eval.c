#include <stdio.h>

int add(int x, int y) {
    return x + y;
}

int print_int(int x) {
    printf("%d\n", x);
    return x;
}

int main(void) {
    int x = 1, y = 2, z = 0;

    // UNSPECIFIED: x cannot be used at the same time as being incremented.
    print_int(print_int(x) + x++);

    return 0;
}
