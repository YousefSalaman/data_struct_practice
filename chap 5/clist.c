#include "lists.h"


/* Public circular linked list methods */


// Initialize list object
void init_clist(clist_t * list)
{
    list->size = 0;
    list->head = NULL;
}


// List object constructor
clist_t * create_clist(void)
{
    clist_t * list;

    // Allocate list space
    if ((list = malloc(sizeof(clist_t))) == NULL)
    {
        return NULL;
    }

    init_clist(list);
    return list;
}


// Clear list object
void clear_clist(clist_t * list, void (*destroy_data)(void *))
{
    void * data;

    // Remove nodes and data
    while(list->size > 0)
    {
        if ((data = remove_clist_node(list, list->head)) != NULL)
        {
            destroy_data(data);
        }
    }

    memset(list, 0, sizeof(clist_t)); // Clear list object struct
}


// List object destructor
void destroy_clist(clist_t * list, void (*destroy_data)(void *))
{
    clear_clist(list, destroy_data);
    free(list);
}


/**Remove next node of given node from list
 * 
 * It returns the node that has been removed from the given list. NULL
 * is not a valid node to enter (since always exists a node pointing
 * to the head if the list is not empty). Code will return NULL if 
 * list is empty or node argument is NULL.
 */
clist_node_t * remove_clist_node(clist_t * list, clist_node_t * node)
{
    // If list is empty or node is NULL, do not do anything
    if (list->size == 0 || node == NULL)
    {
        return NULL;
    }

    clist_node_t * old_node = node->next;  // Node to remove

    // Adjust pointers and size in list
    list->size--;
    node->next = old_node->next;
    if (old_node == list->head)
    {
        list->head = (list->size == 0)? NULL: old_node->next;  // If last element on list, set list head to NULL. Otherwise, set next node
    }

    return old_node;
}


/**Remove and delete next node of given node from list
 *
 * Returns data that was stored in next node, and if an incorrect
 * deletion was requested, then it will return NULL.
 */
void * delete_clist_node(clist_t * list, clist_node_t * node)
{
    clist_node_t * old_node = remove_clist_node(list, node);
    void * data = (old_node != NULL)? old_node->data: NULL;

    free(old_node);

    return data;
}


/**Insert new node next to given node from list
 * 
 * This one does not create a new node for the given list. It just 
 * places a new node next to the given node. If you also want to
 * create a new node and place data in it, use the add_clist_node
 * clist method. To insert a node in the list head, you have to 
 * input NULL in the node argument.
 * 
 * Note that the node argument must be from the list and new_node
 * is a node that is not from the list.
 */
void insert_clist_node(clist_t * list, clist_node_t * restrict node, clist_node_t * restrict new_node)
{
    clist_node_t ** old_node = (node == NULL)? &list->head: &node->next;  // Where new node will be placed

    new_node->next = (*old_node == NULL)? new_node: *old_node;  // If list is empty, link new head to itself. Otherwise, link the old node 
    *old_node = new_node;

    list->size++;  // Update list size
}


/**Create and insert new node next to given node from list
 * 
 * Returns true if it was successful in doing so. Otherwise, it
 * returns false (because there is no more space left).
 */
bool add_clist_node(clist_t * list, clist_node_t * node, const void * data)
{
    clist_node_t * new_node;

    // Allocate list node storage
    if ((new_node = malloc(sizeof(clist_node_t))) == NULL)
    {
        return false;  // If no storage is available
    }

    new_node->data = (void *) data;  // Place data in new node
    insert_clist_node(list, node, new_node);
    
    return true;
}
