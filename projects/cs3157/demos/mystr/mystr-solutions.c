#include <stdio.h>
#include <stdlib.h>

#include "mystr.h"

struct mystr *solutions_mystr_copy(const struct mystr *this) {
    char *s = mystr_to_str(this);
    struct mystr *copy = mystr_new(s);
    free(s);
    return copy;
}

int solutions_mystr_equals(const struct mystr *this, const struct mystr *r) {
    if (this->len != r->len)
        return 0;

    for (int i = 0; i < this->len; i++)
        if (this->data[i] != r->data[i])
            return 0;

    return 1;
}

void solutions_mystr_append(struct mystr *this, const struct mystr *r) {
    if (mystr_is_empty(this) && mystr_is_empty(r))
        // If both strings are empty, don't do anything.
        return;

    char *old_data = this->data;
    size_t old_len = this->len;

    this->len = old_len + r->len;
    this->data = malloc(this->len);

    for (int i = 0; i < old_len; i++)
        this->data[i] = old_data[i];

    for (int i = old_len; i < this->len; i++)
        this->data[i] = r->data[i - old_len];

    free(old_data);
}

void solutions_mystr_truncate(struct mystr *this, size_t begin, size_t end) {
    if (mystr_is_empty(this))
        return;

    if (begin >= this->len || end <= 0 || end <= begin) {
        free(this->data);
        this->len = 0;
        this->data = NULL;
        return;
    }

    if (end > this->len)
      end = this->len;

    char *old_data = this->data;

    this->len = end - begin;
    this->data = malloc(this->len);

    for (int i = 0; begin + i < end; i++)
        this->data[i] = old_data[begin + i];

    free(old_data);
}
