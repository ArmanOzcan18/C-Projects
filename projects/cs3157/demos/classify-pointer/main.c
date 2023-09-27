#include <stdlib.h>

int on_stack(const void *p) {
    // While we are executing on_stack(), its stack frame is necessarily at the
    // bottom of the stack (i.e., most recently pushed onto the downward-growing
    // stack).  This means that on_stack()'s local variable, p, represents the
    // "frontier" of the stack; anything else in the stack must be above it.
    //
    // So, we can compare p's address to the address it points to determine
    // whether p points to something on the stack (in which case p will point to
    // a higher address than itself).
    return (void *)&p < p;
}

/** Given a pointer p, classify_pointer():
 *
 *      prints "STACK" if p contains an address on the stack;
 *      prints "HEAP" if p contains an address on the heap;
 *      prints "NEITHER" otherwise.
 */
void classify_pointer(const void *p);

int g = 0;
int *h = &g;

void cp(int **a) {
    // At this point, a points to h, which points to g.

    int *x = *a;

    // x is set to *a, i.e., h. In other words, x = h = &g.

    a = &x;

    // a now points to x.

    classify_pointer(x);        // (4.1.2) NEITHER: x points to g
    classify_pointer(&a);       // (4.1.3) STACK: a is a local variable
    classify_pointer(a);        // (4.1.4) STACK: a points to x

    // x now points to the beginning of some heap-allocated memory.

    *a = malloc(sizeof(int) * 100);

    classify_pointer(a);        // (4.1.5) STACK: a still points to x
    classify_pointer(++*a);     // (4.1.6) HEAP: x points to heap

    // Because of ++*a, x points to 4 bytes past what malloc() returned.

    h = x;

    // And now h also points there.
}

int main(void) {
    cp(&h);

    // (4.1.7) INSERT HERE
    // Without freeing the memory we allocated on the heap, we are leaking
    // sizeof(int) * 100 = 400 bytes.
    //
    // h points to +1 (4 bytes) past what malloc() returned; we may only free()
    // exactly what malloc() returned us, so we need to -1 to compensate.
    free(h - 1);

    return 0;
}
