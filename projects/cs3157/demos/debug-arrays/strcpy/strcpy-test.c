#include <stdio.h>

char *mystrcpy(char *dest, char *src) {
    while ((*dest++ = *src++) != 0) ;

    // This returns the wrong pointer! strcpy() is supposed to
    // return a pointer to the dest it was given, but dest now
    // points to a null terminator byte.
    return dest;
}

int main(void) {
    char a[4] = "123";
    char b[4];
    char *p = mystrcpy(b, a);

    printf("a =  \"%s\"\n", a);
    printf("b =  \"%s\"\n", b);
    printf("p -> \"%s\"\n", p);

    return 0;
}
