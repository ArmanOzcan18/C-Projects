#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2)
        fprintf(stderr, "Warning: no arguments given.\n");
    else
        fprintf(stderr, "%d arguments given.\n", argc - 1);

    for (int i = 1; i < argc; i++)
        fprintf(stdout, "%s\n", argv[i]);

    return 0;
}
