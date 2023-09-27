#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *fgmalloc(size_t size);
void fgfree(void *p);
extern int fg_a, fg_b; // fg_a and fg_b are declared but not defined

int main(int argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "A %d %d\n", fg_a, fg_b);
        return 0;
    }

    char **copy = fgmalloc(argc * sizeof(char *));

    fprintf(stderr, "B %d %d\n", fg_a, fg_b);

    for (int i = 0; i < argc; i++) {

        size_t len = sizeof(argv[i]);
        copy[i] = fgmalloc(len + 1);

        strcpy(copy[i], argv[i]);     // Copy argv[i] to copy[i]

        copy[i][sizeof(copy[i]) / 2] = '\0';
    }

    fprintf(stderr, "C %d %d\n", fg_a, fg_b);

    for (int i = 0; i < argc; i++) {
        printf("%s\n", copy[i]);
        fgfree(copy[i]);
    }

    char *args[] = { argv[0], NULL };
    execv(*args, args);

    fgfree(copy);
    fprintf(stderr, "D %d %d\n", fg_a, fg_b);
}
