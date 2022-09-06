#include <string.h>
#include <stdlib.h>

#include "lists.h"


/* Public singly-linked list methods */

// Initialize list object
void init_list(list_t * list)
{
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
}


// list_t object constructor
list_t * create_list(void)
{
    list_t * list;

    // Allocate list space
    if ((list = malloc(sizeof(list_t))) == NULL)
    {
        return NULL;
    }

    init_list(list);
    return list;
}


// Clear list object
void clear_list(list_t * list, void (*destroy_data)(void *))
{
    void * data;

    // Remove nodes and data
    while(list->size > 0)
    {
        if ((data = delete_list_node(list, NULL)) != NULL)
        {
            destroy_data(data);
        }
    }

    memset(list, 0, sizeof(list_t)); // Clear list object struct
}


// list_t object destructor
void destroy_list(list_t * list, void (*destroy_data)(void *))
{
    clear_list(list, destroy_data);
    free(list);
}



list_node_t * remove_list_node(list_t * list, list_node_t * node)
{
    list_node_t ** rm_node = (node == NULL)? &list->head: &node->next;  // Node to remove
    list_node_t * old_node = *rm_node;  

    // If out-of-bounds or list is empty, do not do anything
    if (old_node == NULL)
    {
        return NULL;
    }

    // Adjust list tail if this is the one being removed
    if (old_node->next == NULL)
    {
        list->tail = node;
    }

    // Adjust pointers and list size
    *rm_node = old_node->next;
    list->size--;

    return old_node;
}


/**Remove and delete next node of given node from list
 *
 * Returns data that was stored in next node, and if an incorrect
 * deletion was requested, then it will return NULL.
 */
void * delete_list_node(list_t * list, list_node_t * node)
{
    list_node_t * old_node = remove_list_node(list, node);
    void * data = (old_node != NULL)? old_node->data: NULL;

    free(old_node);

    return data;
}


/**Insert new node next to given node from list
 * 
 * This one does not create a new node for the given list. It just 
 * places a new node next to the given node. If you also want to
 * create a new node and place data in it, use the add_list_node
 * list method.
 * 
 * Note that the node argument must be from the list and new_node
 * is a node that is not in the list.
 */
void insert_list_node(list_t * list, list_node_t * restrict node, list_node_t * restrict new_node)
{
    list_node_t ** old_node = (node == NULL)? &list->head: &node->next;  // Where new node will be placed

    // If new node will be placed at tail 
    if ((*old_node) == NULL)
    {
        list->tail = new_node;
    }

    // Adjust list to insert new node
    new_node->next = *old_node;
    *old_node = new_node;

    list->size++;  // Update list size
}


/**Create and insert new node next to given node from given list
 * 
 * Returns true if list node was created for the given list. Otherwise,
 * it will return false (i.e., no space was left to allocate new list
 * node.)
*/
bool add_list_node(list_t * list, list_node_t * node, const void * data)
{
    list_node_t * new_node;

    // Allocate list node storage
    if ((new_node = malloc(sizeof(list_node_t))) == NULL)
    {
        return false;  // If no storage is available
    }

    new_node->data = (void *) data;  // Place data in new node
    insert_list_node(list, node, new_node);
    
    return true;
}


/**Confirm if data is in given list
 * 
 * Returns true if the given comparison function "match" returns true
 * for the given data and a piece of data stored in the given list. 
 * Otherwise, it will return false.
 */
bool in_list(list_t * list, const void * data, bool (*match)(void *, void *))
{
    for (list_node_t * node = list->head; node != NULL; node = node->next)
    {
        if (match(data, node->data))
        {
            return true;
        }
    }
    return false;
}