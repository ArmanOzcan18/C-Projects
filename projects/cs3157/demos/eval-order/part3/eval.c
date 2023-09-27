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

    // UNSPECIFIED: order of evaluation for arithmetic operands is unspecified.
    print_int(print_int(y) - print_int(x));

    return 0;
}
