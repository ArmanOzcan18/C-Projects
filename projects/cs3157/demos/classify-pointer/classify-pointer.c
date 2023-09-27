#include <stdio.h>
#include <unistd.h>

/** Given a pointer p, classify_pointer():
 *
 *      prints "STACK" if p contains an address on the stack;
 *      prints "HEAP" if p contains an address on the heap;
 *      prints "NEITHER" otherwise.
 */
void classify_pointer(const void *p) {
    // sbrk(0) returns the program break -- i.e., the top of the heap
    void *heap_top = sbrk(0);

    // ld adds the symbol _end for the end of all segments in ELF
    extern void *_end;
    void *heap_bottom = &_end;

    if ((void *) &p < p)
        printf("%s\t%p\t", "STACK", p);
    else if (heap_bottom <= p && p < heap_top)
        printf("%s\t%p\t", "HEAP", p);
    else
        printf("%s\t%p\t", "NEITHER", p);

    printf("(heap: %p<-->%p)\n", heap_bottom, heap_top);
}
