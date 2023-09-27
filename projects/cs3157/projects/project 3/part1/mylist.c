#include <stdlib.h>
#include "mylist.h"

/*
 * A node in a linked list.

struct Node {
    void *data;
    struct Node *next;
};


 * A linked list.
 * 'head' points to the first node in the list, or is NULL if empty.

struct List {
    struct Node *head;
};

 * Initialize an empty list.

static inline void initList(struct List *list)
{
    list->head = NULL;
}


 * In all functions below, the 'list' parameter is assumed to point to
 * a valid struct List.
 */

/*
 * Create a node that holds the given data pointer,
 * and add the node to the front of the list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 *
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addFront(struct List *list, void *data){
    struct Node *n = malloc(sizeof(struct Node));
    if(n == NULL)  
        return NULL;
    n->data = data;
    n->next = list->head;
    list->head = n;
    return n;
}

/*
 * Traverse the list, calling f() with each data item.
 */
void traverseList(struct List *list, void (*f)(void *)){
    struct Node *n = list->head;
    while(n != NULL){
        (*f)(n->data);
        n = n->next;
    }
}

/*
 * Traverse the list, comparing each data item with 'dataSought' using
 * 'compar' function.  ('compar' returns 0 if the data pointed to by
 * the two parameters are equal, non-zero value otherwise.)
 *
 * Returns the first node containing the matching data,
 * NULL if not found.
 */
struct Node *findNode(struct List *list, const void *dataSought, int (*compar)(const void *, const void *)){
    struct Node *n = list->head;
    while(n != NULL){
        if(!(*compar)(dataSought,n->data))
            return n;
        n = n->next;
    }
    return NULL;
}

/*
 * Flip the sign of the double value pointed to by 'data' by
 * multiplying -1 to it and putting the result back into the memory
 * location.
 */
void flipSignDouble(void *data){
    if(data == NULL)
        return;

    double *temp = (double *) data;
    *temp *= -1;   
    return;
}

/*
 * Compare two double values pointed to by the two pointers.
 * Return 0 if they are the same value, 1 otherwise.
 */
int compareDouble(const void *data1, const void *data2){
    if(data1 == NULL || data2 == NULL)
        return 1;

    double *double1 = (double *) data1; 
    double *double2 = (double *) data2;
   
    if(*double1 == *double2)
        return 0;
    
    return 1;
    
}

/*
 * Remove the first node from the list, deallocate the memory for the
 * node, and return the 'data' pointer that was stored in the node.
 * Returns NULL is the list is empty.
 */
void *popFront(struct List *list){
    if(isEmptyList(list))
        return NULL;
    struct Node *n = list->head;
    void *data = n->data;
    list->head = n->next;
    free(n);
   
    return data;
}

/*
 * Remove all nodes from the list, deallocating the memory for the
 * nodes.  You can implement this function using popFront().
 */
void removeAllNodes(struct List *list){
    while(popFront(list) != NULL);
    return;
}

/*
 * Create a node that holds the given data pointer,
 * and add the node right after the node passed in as the 'prevNode'
 * parameter.  If 'prevNode' is NULL, this function is equivalent to
 * addFront().
 *
 * Note that prevNode, if not NULL, is assumed to be one of the nodes
 * in the given list.  The behavior of this function is undefined if
 * prevNode does not belong in the given list.
 *
 * Note that this function does not manage the lifetime of the object
 * pointed to by 'data'.
 *
 * It returns the newly created node on success and NULL on failure.
 */
struct Node *addAfter(struct List *list, struct Node *prevNode, void *data){
   if(prevNode == NULL)
       return addFront(list, data);

   struct Node *n = malloc(sizeof(struct Node));
   if(n == NULL)
       return NULL;

   n->data = data;

   struct Node * compNode = list->head;
   while(compNode != NULL){
       if(compNode == prevNode){
           n->next = compNode->next;
           compNode->next = n;
           return n;
       }
       compNode = compNode->next;
   }
 
   return NULL;
}

/*
 * Reverse the list.
 *
 * Note that this function reverses the list purely by manipulating
 * pointers.  It does NOT call malloc() directly or indirectly (which
 * means that it does not call addFront() or addAfter()).
 *
 * Implementation hint: keep track of 3 consecutive nodes (previous,
 * current, next) and move them along in a while loop.  Your function
 * should start like this:
 *
 *    struct Node *prv = NULL;
 *    struct Node *cur = list->head;
 *    struct Node *nxt;
 *
 *    while (cur)
 *        ...
 *
 * And at the end, prv will end up pointing to the first element of
 * the reversed list.  Don't forget to assign it to list->head.
 */
void reverseList(struct List *list){
    struct Node *prv = NULL;
    struct Node *cur = list->head;
    struct Node *nxt;

    while(cur){
        nxt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nxt;
    }

    list->head = prv;
    return;
}

