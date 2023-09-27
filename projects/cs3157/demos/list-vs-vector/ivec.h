#ifndef _IVEC_H_
#define _IVEC_H_

/*
 * A vector of integers.
 *
 * A vector is a resizeable array.  When we reach capacity, we allocate a new
 * data array that is double the size and move everything there.
 */
struct long_vec {
    long *data;     // Pointer to heap-allocated array.
    size_t len;     // How many array slots currently used in data.
    size_t cap;     // How many array slots available in data.
};

/*
 * Initialize an empty vector. O(1).
 */
static inline void long_vec_init(struct long_vec *vec)
{
    vec->data = NULL;
    vec->len = vec->cap = 0;
}

/*
 * Returns non-zero if the vector is empty, zero otherwise. O(1).
 */
static inline long long_vec_is_empty(struct long_vec *vec)
{
    return vec->len == 0;
}

/*
 * Add an integer to the front of the vector. O(n).
 */
long *long_vec_add_front(struct long_vec *vec, long i);

/*
 * Remove the first integer from the vector. O(n).
 */
long long_vec_pop_front(struct long_vec *vec);

/*
 * Reverse the vector. O(n).
 */
void long_vec_reverse(struct long_vec *vec);

/*
 * Remove all integers from the vector. O(1).
 */
void long_vec_remove_all(struct long_vec *vec);

#endif /* #ifndef _IVEC_H_ */
