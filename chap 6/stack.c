#include <string.h>
#include <stdlib.h>

#include "stack.h"


/* Public stack methods */


/**Pop head node from stack
 * 
 * It returns the node that has been removed from the given stack.
 * Code will return NULL if is stack is empty.
 */
stack_node_t * pop_node(stack_t * stack)
{
    stack_node_t * old_node = stack->head;  

    // If stack is empty, do not do anything
    if (old_node == NULL)
    {
        return NULL;
    }

    // Adjust pointers and stack size
    stack->head = old_node->next;
    stack->size--;

    return old_node;
}


/**Remove and delete next node of given node from stack
 *
 * Returns data that was stored in next node, and if an incorrect
 * deletion was requested, then it will return NULL.
 */
void * get_stack_data(stack_t * stack)
{
    stack_node_t * old_node = pop_node(stack);
    void * data = (old_node != NULL)? old_node->data: NULL;

    free(old_node);

    return data;
}


/**Insert new node next to given node from stack
 * 
 * This one does not create a new node for the given stack. It just 
 * places a new node next to the given node. If you also want to
 * create a new node and place data in it, use the add_stack_node
 * stack method.
 * 
 * Note that the node argument must be from the stack and new_node
 * is a node that is not in the stack.
 */
void push_node(stack_t * stack, stack_node_t * new_node)
{
    // Adjust stack to insert new node
    new_node->next = stack->head;
    stack->head = new_node;

    stack->size++;  // Update stack size
}


/**Create and insert new node next to given node from given stack
 * 
 * Returns true if stack node was created for the given stack. Otherwise,
 * it will return false (i.e., no space was left to allocate new stack
 * node.)
*/
bool put_stack_data(stack_t * stack, const void * data)
{
    stack_node_t * new_node;

    // Allocate stack node storage
    if ((new_node = malloc(sizeof(stack_node_t))) == NULL)
    {
        return false;  // If no storage is available
    }

    new_node->data = (void *) data;  // Place data in new node
    push_node(stack, new_node);
    
    return true;
}


/**Confirm if data is in given stack
 * 
 * Returns true if the given comparison function "match" returns true
 * for the given data and a piece of data stored in the given stack. 
 * Otherwise, it will return false.
 */
bool in_stack(stack_t * stack, const void * data, bool (*match)(void *, void *))
{
    for (stack_node_t * node = stack->head; node != NULL; node = node->next)
    {
        if (match(data, node->data))
        {
            return true;
        }
    }
    return false;
}