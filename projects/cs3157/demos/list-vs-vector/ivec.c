#include <stdlib.h>
#include "ivec.h"

#define INIT_CAP 8

/** Ensure capacity to add one more element to the heap-allocated array. */
static void ensure_cap(struct long_vec *vec)
{
    if (vec->data == NULL) {
        /*
         * Uninitialized vector; allocate fresh array with initialial cap=8.
         */
        vec->cap = INIT_CAP;
        vec->data = malloc(sizeof(long) * vec->cap);
    } else if (vec->len == vec->cap) {
        /*
         * Not enough space; double the capacity.
         */
        vec->cap *= 2;

        // Allocate new array.
        long *data = malloc(sizeof(long) * vec->cap);

        // Move old elements to newly-allocated array.
        for (size_t j = 0; j < vec->len; j++)
            data[j] = vec->data[j];

        // free() old array and use new array.
        free(vec->data);
        vec->data = data;
    }
}

long *long_vec_add_front(struct long_vec *vec, long i)
{
    ensure_cap(vec);

    // Shift each old element one position to the right. O(n).
    for (size_t j = vec->len; j > 0; j--)
        vec->data[j] = vec->data[j - 1];

    // Add i to front of data array. O(1).
    vec->len++;
    vec->data[0] = i;

    return &vec->data[0];
}

long long_vec_pop_front(struct long_vec *vec)
{
    if (long_vec_is_empty(vec))
        return 0;

    long i = vec->data[0];

    vec->len--;

    // Shift each element one position to the left. O(n).
    for (size_t j = 0; j < vec->len; j++)
        vec->data[j] = vec->data[j + 1];

    return i;
}

void long_vec_reverse(struct long_vec *vec)
{
    // In-place; swap first with last, second with second last, etc. O(n).
    for (size_t j = 0, k = vec->len - 1; j < k; j++, k--) {
        long i = vec->data[j];
        vec->data[j] = vec->data[k];
        vec->data[k] = i;
    }
}

void long_vec_remove_all(struct long_vec *vec)
{
    // Free array and reinitialize. O(1).
    free(vec->data);
    long_vec_init(vec);
}
