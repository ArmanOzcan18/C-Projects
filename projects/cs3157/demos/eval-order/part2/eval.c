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

    // UNSPECIFIED: incrementing the same variable in two arguments is UB.
    print_int(add(++x, ++x));

    return 0;
}
