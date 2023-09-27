#include <stdlib.h>
#include "ilist.h"

struct long_node *long_list_add_front(struct long_list *list, long data)
{
    struct long_node *node = (struct long_node *)malloc(sizeof(struct long_node));
    if (node == NULL)
        return NULL;

    node->data = data;
    node->next = list->head;
    list->head = node;
    return node;
}

long long_list_pop_front(struct long_list *list)
{
    if (long_list_is_empty(list))
        return 0;

    struct long_node *old_head = list->head;
    long data = old_head->data;

    list->head = old_head->next;
    free(old_head);

    return data;
}

void long_list_reverse(struct long_list *list)
{
    struct long_node *prv = NULL;
    struct long_node *cur = list->head;
    struct long_node *nxt;

    while (cur) {
        nxt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nxt;
    }

    list->head = prv;
}

void long_list_remove_all(struct long_list *list)
{
    while (!long_list_is_empty(list))
        long_list_pop_front(list);
}
