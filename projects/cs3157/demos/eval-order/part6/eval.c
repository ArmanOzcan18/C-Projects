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

    // UNSPECIFIED: order of evaluation of function arguments is unspecified.
    print_int(add(print_int(x), print_int(y)));

    return 0;
}
