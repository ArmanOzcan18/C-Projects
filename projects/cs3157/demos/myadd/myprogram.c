#include <stdio.h>

// This pulls in a declaration for the add symbol.
#include "myadd.h"

// Declare mod here; the symbol is defined in mymod.c.
int mod(int x, int y);

int main(int argc, char **argv) {
    printf("add(3, 4) returned: %d\n", add(3, 4));
    printf("mod(17, 5) returned: %d\n", mod(17, 5));
    return 0;
}
