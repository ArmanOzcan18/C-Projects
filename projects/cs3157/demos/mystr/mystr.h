#ifndef _MYSTR_H
#define _MYSTR_H

struct mystr {
    size_t len;   // Length of the string
    char *data;   // Pointer to array of characters; not null-terminated
};

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
struct mystr *mystr_new(const char *s);

/** Destructor for struct mystr.
 *
 *  Frees the heap memory associated with a struct mystr object and its data.
 *
 *  The caller is responsible for ensuring that dangling pointers to the
 *  now-freed struct mystr aren't used after this is deleted.
 */
void mystr_delete(struct mystr *this);

/** Whether this is an empty string. */
int mystr_is_empty(const struct mystr *this);

/** "Export" a struct mystr as a heap-allocated C string.
 *
 *  Returns a pointer to a heap-allocated, null-terminated C string with
 *  this->data.
 *
 *  The caller is responsible for freeing the allocated C string.
 */
char *mystr_to_str(const struct mystr *this);

/** Make a copy of this struct mystr. */
struct mystr *mystr_copy(const struct mystr *this);

/** Compare two struct mystr objects for equality.
 *
 *  Returns 1 if the contents of l and r are identical; returns 0 otherwise.
 */
int mystr_equals(const struct mystr *this, const struct mystr *r);

/** Append the contents of r to this. */
void mystr_append(struct mystr *this, const struct mystr *r);

/** Shorten this from an inclusive begin index and an exclusive end index. */
void mystr_truncate(struct mystr *this, size_t begin, size_t end);

/** Print out a mystr. */
void mystr_print(const struct mystr *this);

struct mystr *solutions_mystr_copy(const struct mystr *this);
int solutions_mystr_equals(const struct mystr *l,  const struct mystr *r);
void solutions_mystr_append(struct mystr *this, const struct mystr *r);
void solutions_mystr_truncate(struct mystr *this, size_t begin, size_t end);

#endif
