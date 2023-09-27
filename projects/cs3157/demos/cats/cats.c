#include <stdio.h>

int main(void) {
    char buf[8];

    fgets(buf, 8, stdin);
    fputs(buf, stdout);

    return 0;
}
