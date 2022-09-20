
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
        if ((data = delete_dlist_node(list, NULL)) != NULL)
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


bool insert_next_dlist_node(dlist_t * list, dlist_node_t * restrict node, dlist_node_t * restrict new_node)
{
    // NULL is not a valid entry if list is not empty
    if (node == NULL && list->size != 0 || new_node == NULL)
    {
        return false;
    }

    dlist_node_t ** old_node = (node == NULL)? &list->head: &node->next;

    // Adjust new node pointers
    new_node->next = *old_node;
    new_node->prev = node;

    if (list->size == 0)
    {
        list->head = new_node;
    }
    else
    {
        if (node->next == NULL)
        {
            list->tail = new_node;
        }
        else
        {
            node->next->prev = new_node;
        }
    }

    *old_node = new_node;

    list->size++;

    return true;
}


bool insert_prev_dlist_node(dlist_t * list, dlist_node_t * restrict node, dlist_node_t * restrict new_node)
{
    // NULL is not a valid entry if list is not empty
    if (node == NULL && list->size != 0 || new_node == NULL)
    {
        return false;
    }

    dlist_node_t ** old_node = (node == NULL)? &list->head: &node->prev;

    // Adjust new node pointers
    new_node->prev = *old_node;
    new_node->next = node;

    if (list->size == 0)  // Handle insertion when list is empty
    {
        list->tail = new_node;
    }
    else  // Handle insertion when the list is not empty
    {
        if (node->prev == NULL)
        {
            list->head = new_node;
        }
        else
        {
            node->prev->next = new_node;
        }
    }

    *old_node = new_node;

    list->size++;

    return true;
}



bool remove_dlist_node(dlist_t * list, dlist_node_t * node)
{
    dlist_node_t ** prev_node = (node == list->head)? &list->head: &node->prev->next;

    // If node is NULL or list is empty, then do not do anything
    if (node == NULL || list->size == 0)
    {
        return false;
    }

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

    return true;
}


void * delete_dlist_node(dlist_t * list, dlist_node_t * node)
{
    remove_dlist_node(list, node);
    void * data = (node != NULL)? node->data: NULL;

    free(node);

    return data;
}


/**Confirm if data is in given list
 * 
 * Returns true if the given comparison function "match" returns true
 * for the given data and a piece of data stored in the given list. 
 * Otherwise, it will return false.
 */
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


/* Private doubly-linked list messages */

// Shorthand pseudo-private function to add node
bool add_dlist_node_private(dlist_t * list, dlist_node_t * node, const void * data, bool insert_dlist_node(dlist_t *, dlist_node_t * restrict, dlist_node_t * restrict))
{
    dlist_node_t * new_node;

    // Allocate list node storage
    if ((new_node = malloc(sizeof(clist_node_t))) == NULL)
    {
        return false;  // If no storage is available
    }

    new_node->data = (void *) data;  // Place data in new node
    insert_dlist_node(list, node, new_node);
    
    return true;
}