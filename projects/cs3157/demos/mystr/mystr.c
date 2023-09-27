#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mystr.h"

/** Constructor for struct mystr.
 *
 *  The parameter s is a C string that we initialize the struct mystr with.
 *
 *  This constructor returns a pointer to the newly allocated struct mystr
 *  object.
 *
 *  Note that both the struct mystr and the char data it points to are
 *  heap-allocated.  mystr objects should be destroyed using mystr_delete().
 *  All other struct mystr methods should ensure against memory leaks.
 */
struct mystr *mystr_new(const char *s) {
    struct mystr *this = malloc(sizeof(struct mystr));

    this->len = strlen(s);

    if (this->len == 0) {
        // We are initializing an empty string.
        this->data = NULL;
        return this;
    }

    this->data = malloc(this->len);

    for (int i = 0; i < this->len; i++)
        this->data[i] = s[i];

    return this;
}

/** Destructor for struct mystr.
 *
 *  Frees the heap memory associated with a struct mystr object and its data.
 *
 *  The caller is responsible for ensuring that dangling pointers to the
 *  now-freed struct mystr aren't used after this is deleted.
 */
void mystr_delete(struct mystr *this) {
    free(this->data);
    free(this);
}

/** Whether this is an empty string. */
int mystr_is_empty(const struct mystr *this) {
    return this->len == 0;

    // return this->data == NULL;
    // ^ this->data should be NULL when this->len is 0
}

/** "Export" a struct mystr as a heap-allocated C string.
 *
 *  Returns a pointer to a heap-allocated, null-terminated C string with
 *  this->data.
 *
 *  The caller is responsible for freeing the allocated C string.
 */
char *mystr_to_str(const struct mystr *this) {
    char *buf = malloc(this->len + 1);
    for (int i = 0; i < this->len; i++)
        buf[i] = this->data[i];
    buf[this->len] = '\0';
    return buf;
}

/** Make a copy of this struct mystr. */
struct mystr *mystr_copy(const struct mystr *this) {
    // TODO(5.1): replace this with your implementation.
    return solutions_mystr_copy(this);
}

/** Compare two struct mystr objects for equality.
 *
 *  Returns 1 if the contents of l and r are identical; returns 0 otherwise.
 */
int mystr_equals(const struct mystr *this,  const struct mystr *r) {
    // TODO(5.2): replace this with your implementation.
    return solutions_mystr_equals(this, r);
}

/** Append the contents of r to this. */
void mystr_append(struct mystr *this, const struct mystr *r) {
    // TODO(5.3): replace this with your implementation.
    solutions_mystr_append(this, r);
}

/** Shorten this from an inclusive begin index and an exclusive end index. */
void mystr_truncate(struct mystr *this, size_t begin, size_t end) {
    // TODO(5.4): replace this with your implementation.
    solutions_mystr_truncate(this, begin, end);
}

/** Print out a mystr. */
void mystr_print(const struct mystr *this) {
    char *s = mystr_to_str(this);
    printf("%s", s);
    free(s);
}
