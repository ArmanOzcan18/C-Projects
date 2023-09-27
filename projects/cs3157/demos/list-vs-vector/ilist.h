#ifndef _ILIST_H_
#define _ILIST_H_

/*
 * A node in a linked list of integers.
 */
struct long_node {
    long data;
    struct long_node *next;
};

/*
 * A linked list of integers.
 */
struct long_list {
    struct long_node *head;
};

/*
 * Initialize an empty list. O(1).
 */
static inline void long_list_init(struct long_list *list)
{
    list->head = 0;
}

/*
 * Returns non-zero if the list is empty, zero otherwise. O(1).
 */
static inline long long_list_is_empty(struct long_list *list)
{
    return list->head == 0;
}

/*
 * Add an integer to the front of the list. O(1).
 */
struct long_node *long_list_add_front(struct long_list *list, long data);

/*
 * Remove the first node from the list. O(1).
 */
long long_list_pop_front(struct long_list *list);

/*
 * Reverse the list. O(n).
 */
void long_list_reverse(struct long_list *list);

/*
 * Remove all nodes from the list. O(n).
 */
void long_list_remove_all(struct long_list *list);

#endif /* #ifndef _ILIST_H_ */
