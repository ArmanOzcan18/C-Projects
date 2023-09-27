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

    // || is short-circuiting, so print_int(x) is never evaluated.
    print_int(print_int(y) || print_int(x));

    return 0;
}
