#ifndef LISTS_H
#define LISTS_H

#include <stdint.h>
#include <stdbool.h>

/* list_t type definitions */

// list_t nodes in singly-linked list
typedef struct list_node
{
    void *data; //
    struct list_node * next;
} list_node_t;

// list_t nodes in doubly-linked list
typedef struct dlist_node
{
    void *data; //
    struct dlist_node * prev;
    struct dlist_node * next;
} dlist_node_t;

// list_t nodes in circular linked list
typedef struct clist_node
{
    void *data; //
    struct clist_node *next;
} clist_node_t;

// Singly-linked list object
typedef struct list
{
    uint16_t size;
    list_node_t *head;
    list_node_t *tail;
} list_t;

// Doubly-linked list object
typedef struct dlist
{
    uint16_t size;
    dlist_node_t *head;
    dlist_node_t *tail;
} dlist_t;

// Doubly-linked list object
typedef struct clist
{
    uint16_t size;
    clist_node_t *head;
} clist_t;


/* Public singly-list methods */

list_t * create_list(void);

void init_list(list_t * list);

bool add_list_node(list_t * list, list_node_t * node, const void * data);

bool insert_list_node(list_t * list, list_node_t * restrict node, list_node_t * restrict new_node);

list_node_t * remove_list_node(list_t *list, list_node_t *node);

void * delete_list_node(list_t *list, list_node_t *node);

void clear_list(list_t *list, void (*destroy_data)(void *));

void destroy_list(list_t *list, void (*destroy_data)(void *));

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((element) == (list)->head)

#define list_is_tail(element) ((element)->next == NULL)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)


/* Public doubly-linked list methods */

void clear_dlist(dlist_t *list, void (*destroy_data)(void *));

dlist_t *create_dlist(void);

void destroy_dlist(dlist_t *list, void (*destroy_data)(void *));

void init_dlist(dlist_t *list);

bool insert_next_dlist_node(dlist_t *list, dlist_node_t * restrict node, dlist_node_t * restrict new_node);

bool insert_prev_dlist_node(dlist_t *list, dlist_node_t * restrict node, dlist_node_t * restrict new_node);

bool add_dlist_node_private(dlist_t * list, dlist_node_t * node, const void * data, bool insert_dlist_node(dlist_t * list, dlist_node_t * restrict node, dlist_node_t * restrict new_node));

/**Create and insert new node with data next to the given node in the list
 * 
 * Returns true if it was successful in doing so. Otherwise, it
 * returns false (because there is no more space left).
 */
#define add_next_dlist_node(list, node, data) add_dlist_node_private(list, node, data, insert_next_dlist_node)

/**Create and insert new node with data before the given node in the list
 * 
 * Returns true if it was successful in doing so. Otherwise, it
 * returns false (because there is no more space left).
 */
#define add_prev_dlist_node(list, node, data) add_dlist_node_private(list, node, data, insert_prev_dlist_node)

bool remove_dlist_node(dlist_t *list, dlist_node_t *node);

void * delete_dlist_node(dlist_t * list, dlist_node_t * node);

#define dlist_size(list) ((list)->size)

#define dlist_head(list) ((list)->head)

#define dlist_tail(list) ((list)->tail)

#define dlist_is_head(list, element) ((element) == (list)->head)

#define dlist_is_tail(element) ((element)->next == NULL)

#define dlist_data(element) ((element)->data)

#define dlist_next(element) ((element)->next)

#define dlist_prev(element) ((element)->next)


/* Public circular list methods */

clist_t *create_clist(void);

void init_clist(clist_t *list);

bool add_clist_node(clist_t * list, clist_node_t * node, const void * data);

bool insert_clist_node(clist_t * list, clist_node_t * restrict node, clist_node_t * restrict new_node);

void clear_clist(clist_t *list, void (*destroy_data)(void *));

void destroy_clist(clist_t *list, void (*destroy_data)(void *));

clist_node_t * remove_clist_node(clist_t * list, clist_node_t * node);

void * delete_clist_node(clist_t * list, clist_node_t * node);

#define clist_size(list) ((list)->size)

#define clist_head(list) ((list)->head)

#define clist_is_head(list, element) ((element) == (list)->head)

#define clist_is_tail(element) ((element)->next == NULL)

#define clist_data(element) ((element)->data)

#define clist_next(element) ((element)->next)

#endif