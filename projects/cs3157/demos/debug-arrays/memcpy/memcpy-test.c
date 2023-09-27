#include <stdio.h>
#include <string.h>

void *mymemcpy(void *dest, void *src, size_t n) {
    char *d = dest, *s = src;
    int i = 0;
    while (i < n)
        // Undefined behavior; incrementing i while reading from it in the same
        // expression is not allowed.  Fix this by incrementing i in a statement
        // on its own, instead of trying to be clever.
        d[i] = s[i++];
    return dest;
}

struct FPoint {
    float x;
    float y;
};

int main(void) {
    struct FPoint pt1 = { .x = 4.2, .y = 2.4 };
    struct FPoint pt2;

    struct FPoint *ptr = mymemcpy(&pt2, &pt1, sizeof(pt1));

    printf("pt1 = struct FPoint { .x = %f, .y = %f }\n", pt1.x, pt1.y);
    printf("pt2 = struct FPoint { .x = %f, .y = %f }\n", pt2.x, pt2.y);
    printf("ptr -> struct FPoint { .x = %f, .y = %f }\n", ptr->x, ptr->y);

    return 0;
}
