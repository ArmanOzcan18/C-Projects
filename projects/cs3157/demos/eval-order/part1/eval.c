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

    if (print_int(z))  // Condition evaluates to if(0), and goes to else branch.
        print_int(y);
     else
        print_int(x);

    return 0;
}
