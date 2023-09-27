#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ilist.h"
#include "ivec.h"

long ilist_bench(size_t rounds, int reverse)
{
    struct long_list l;
    long_list_init(&l);

    long i = 1;
    for (size_t r = 0; r < rounds; r++) {

        // If i is growing too large, truncate it to avoid overflow.
        while (i > 1 << 16)
            i >>= 1;

        long_list_add_front(&l, i);

        if (reverse)
            long_list_reverse(&l);

        i = 0;
        for (struct long_node *n = l.head; n; n = n->next)
            i += n->data;
    }

    long_list_remove_all(&l);

    return i;
}

long ivec_bench(size_t rounds, int reverse)
{
    struct long_vec v;
    long_vec_init(&v);

    long i = 1;
    for (long r = 0; r < rounds; r++) {

        // If i is growing too large, truncate it to avoid overflow.
        while (i > 1 << 16)
            i >>= 1;

        long_vec_add_front(&v, i);

        if (reverse)
            long_vec_reverse(&v);

        i = 0;
        for (long n = 0; n < v.len; n++)
            i += v.data[n];
    }

    long_vec_remove_all(&v);

    return i;
}


int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("usage: %s <test> <rounds>\n", *argv);
        exit(1);
    }

    long rounds = atoi(argv[2]);

    // If rounds is negative, then reverse list during benchmark.
    int reverse = rounds < 0;

    // Restore rounds to positive value.
    rounds = rounds < 0 ? -rounds : rounds;

    long result;

    if (argv[1][0] == 'l')
        result = ilist_bench(rounds, reverse);
    else
        result = ivec_bench(rounds, reverse);

    printf("Result: %ld\n", result);

    return 0;
}
