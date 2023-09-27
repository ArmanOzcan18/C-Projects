#include <stdlib.h>
#include <stdio.h>

int fg_a = 0, fg_b = 0;

void *fgmalloc(size_t size)
{
    size_t *h = malloc(size + sizeof(size));

    *h = size;

    fg_a += size;
    fg_b++;

    return h + 1;
}

void fgfree(void *p)
{
  size_t *h = p;

  fg_a -= h[-1];
  fg_b--;

  free(h - 1);
}
