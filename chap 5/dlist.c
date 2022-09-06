
#include <string.h>
#include <stdlib.h>

#include "lists.h"


// Function prototypes


/* Public doubly-linked list methods */

// Initialize dlist method
void init_dlist(dlist_t * list)
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}


// Doubly linked list object constructor
dlist_t * create_dlist(void)
{
    dlist_t * list;

    // Allocate list space
    if ((list = malloc(sizeof(dlist_t))) == NULL)
    {
        return NULL;
    }

    init_list(list);
    return list;
}


// Clear doubly linked list object
void clear_dlist(dlist_t * list, void (*destroy_data)(void *))
{
    void * data;

    // Remove nodes and data
    while(list->size > 0)
    {
        if ((data = remove_dlist_node(list, NULL)) != NULL)
        {
            destroy_data(data);
        }
    }

    memset(list, 0, sizeof(dlist_t)); // Clear list object struct
}


// Doubly linked list object destructor
void destroy_dlist(dlist_t * list, void (*destroy_data)(void *))
{
    clear_dlist(list, destroy_data);
    free(list);
}


bool insert_next_dlist_node(dlist_t * list, dlist_node_t * node, const void * data)
{
    dlist_node_t * new_node;
    dlist_node_t ** old_node = (node == NULL)? &list->head: node->next;

    // No placement allowed if list is empty and allocate space for node
    if ((node == NULL && list->size != 0) || (new_node = malloc(sizeof(dlist_node_t))) == NULL)
    {
        return false;
    }

    // Handle dlist insertion
    new_node->data = (void *) data;
    new_node->next = *old_node;
    new_node->prev = node;

    if ((*old_node) == NULL)
    {
        list->tail = new_node;
    }
    else
    {
        node->next->prev = new_node;
    }

    *old_node = new_node;

    list->size++;  // Update list size

    return true;
}


bool insert_prev_dlist_node(dlist_t * list, dlist_node_t * node, const void * data)
{
    dlist_node_t * new_node;
    dlist_node_t ** old_node = (node == NULL)? &list->head: node->prev;

    // No placement allowed if list is empty and allocate space for node
    if ((node == NULL && list->size != 0) || (new_node = malloc(sizeof(dlist_node_t))) == NULL)
    {
        return false;
    }

    // Handle dlist insertion
    new_node->data = (void *) data;
    new_node->prev = *old_node;
    new_node->next = node;

    if ((*old_node) == NULL)
    {
        list->head = new_node;
    }
    else
    {
        node->prev->next = new_node;
    }

    *old_node = new_node;

    list->size++;  // Update list size

    return true;
}


void * remove_dlist_node(dlist_t * list, dlist_node_t * node)
{
    dlist_node_t ** prev_node = (node == list->head)? &list->head: &node->prev->next;

    // If node is NULL or list is empty, then do not do anything
    if (node == NULL || list->size == 0)
    {
        return NULL;
    }

    void * data = node->data; // Fetch data

    // Handle node removal
    if (node->next == NULL)
    {
        list->tail = node->prev;
    }
    else
    {
        node->next->prev = node->prev;
    }
    *prev_node = node->next;

    // Do final adjustments
    list->size--;
    free(node);

    return data;
}



bool in_dlist(dlist_t * list, const void * data, bool (*match) (void *, void *))
{
    for (dlist_node_t * node = list->head; node != NULL; node = node->next)
    {
        if (match(data, node->data))
        {
            return true;
        }
    }
    return false;
}