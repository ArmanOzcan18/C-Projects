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

    // This one is tricky. Work it out on paper before running ./eval!
    while (print_int(y--) || print_int(--x))
          print_int(z);

    return 0;
}
