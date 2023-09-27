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

    // Order of evaluation for && (and ||) is well-defined; print_int(z)
    // evaluates to 0, so the program never enters the while loop.
    while(print_int(y) && print_int(z))
        print_int(x);

    return 0;
}
