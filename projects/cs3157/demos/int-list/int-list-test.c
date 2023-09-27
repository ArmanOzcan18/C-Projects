#include <stdio.h>
#include "int-list.h"

int main(void) {

    struct Node *l = create2Nodes(1, 2);

    printf("first element is at address: %p\n", (void *) l);
    printf("first element holds the number: %d\n", l->data);

    printf("second element is at address: %p\n", (void *) l->next);
    printf("second element holds the number: %d\n", l->next->data);

    printf("third element (if any) is at address %p\n", (void *) l->next->next);
    return 0;
}
