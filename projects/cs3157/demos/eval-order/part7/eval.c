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

    // sizeof does not evaluate its argument, so behavior here is well-defined.
    print_int(sizeof(print_int(x)) - sizeof(print_int(y)));

    return 0;
}
