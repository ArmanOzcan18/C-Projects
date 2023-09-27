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

    // Incrementing two different variables is OK (though not best practice).
    print_int(add(y++, ++z));

    return 0;
}
