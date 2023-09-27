#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <assert.h>

void *fgmalloc(size_t size);
void fgfree(void);
extern int fg_a, fg_b; // fg_a and fg_b are declared but not defined

int main(void) {
    int *i = fgmalloc(sizeof(int) * 3);

    i[0] = htonl(31);
    i[1] = ntohl(0x507 + i[0]);
    i[2] = '0' << 8;

    fwrite(i, sizeof(int), 3, stdout);

    assert(fg_a == 12 && fg_b == 1);

    fgfree(i);

    assert(fg_a == 0 && fg_b == 0);

    return 0;
}
