#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static uint64_t MAGIC = ~((uint64_t) 0);

const size_t WAD = sizeof(MAGIC);

void *MALLOC(size_t n) {
    char *p = malloc(2 * WAD + n);
    if (p == NULL)
        return NULL;

    uint32_t *head = (uint32_t *)p;
    head[0] = head[1] = n;
    memcpy(p + WAD + n, &MAGIC, WAD);
    return p + WAD;
}

void FREE(void *p) {
    if (p == NULL) {
        fprintf(stderr, "%s\n", "NULL");
        return;
    }

    uint32_t *head = (uint32_t *)p - 2;
    if (head[0] != head[1] || memcmp((char *)p + head[0], &MAGIC, WAD) != 0)
        fprintf(stderr, "%s\n", "OOPS");
    else
        fprintf(stderr, "%s\n", "OKAY");

    free((char *)p - WAD);
}
