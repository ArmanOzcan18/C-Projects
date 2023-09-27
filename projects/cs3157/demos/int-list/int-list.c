#include <stdlib.h>
#include "int-list.h"

struct Node *create2Nodes(int a, int b) {
    struct Node *head = NULL, *n;

    n = malloc(sizeof(struct Node));
    n->data = b;
    n->next = head;
    head = n;

    n = malloc(sizeof(struct Node));
    n->data = a;
    n->next = head;
    head = n;

    return head;
}
