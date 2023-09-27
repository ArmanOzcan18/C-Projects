#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    setlinebuf(stdout); // Ensure stdout is line-buffered

    printf("i\n");

    char buf[] = "for";

    printf("%s ", buf);

    fork();

    char *str = buf;
    str[0]++;

    printf("%s\n", str);
}
