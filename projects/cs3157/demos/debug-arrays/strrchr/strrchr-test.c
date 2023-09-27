#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrrchr(char *s, char c) {
    int i = sizeof(s);
    // This measures the size of the pointer s, not the length of the array it
    // points to!  This will give you the wrong if s is longer than 8, and
    // probably a memory if s is shorter than 8.
    while (i-- > 0)
        if (s[i] == c)
            return s + i;
    return NULL;
}

void test1(void) {
    char a[16] = "123456789abcdef";
    char *f = mystrrchr(a, 'd');

    if (f) 
        printf("%s\n", f);
    else
        printf("character 'd' not found in string \"%s\"\n", a);
}

void test2(void) {
    char *p = malloc(4);
    strcpy(p, "dbc");
    char *f = mystrrchr(p, 'd');

    if (f) 
        printf("found 'd' in \"%s\"\n", f);
    else
        printf("character 'd' not found in string \"%s\"\n", p);

    free(p);
}


int main(void) {
    test1();
    test2();
    return 0;
}
