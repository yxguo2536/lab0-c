/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;

    while (q->head) {
        list_ele_t *node = q->head;
        q->head = q->head->next;
        free(node->value);
        free(node);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (!q)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    char *newStr = malloc(strlen(s) + 1);
    if (!newStr)
        return false;
    strcpy(newStr, s);

    /* What if either call to malloc returns NULL? */
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        free(newStr);
        return false;
    }

    newh->value = newStr;
    newh->next = q->head;

    if (!q->size)
        q->tail = newh;
    q->head = newh;
    q->size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return false;

    char *newStr = malloc(strlen(s) + 1);
    if (!newStr)
        return false;
    strcpy(newStr, s);

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        free(newStr);
        return false;
    }

    newh->value = newStr;
    newh->next = NULL;

    if (!q->size) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = q->tail->next;
    }
    q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q || !q->head)
        return false;

    list_ele_t *node = q->head;
    q->head = q->head->next;
    q->size--;

    if (sp) {
        strncpy(sp, node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    free(node->value);
    free(node);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !q->head)
        return 0;

    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (!q || !q->head)
        return;

    list_ele_t *prev = NULL;
    list_ele_t *cur = q->head;

    q->tail = q->head;
    while (cur) {
        q->head = cur;
        cur = cur->next;

        q->head->next = prev;

        prev = q->head;
    }
}
