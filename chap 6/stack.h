#ifndef STACK_H
#define STACK_H

#include "../chap 5/lists.h"

/* Stack objects */

typedef clist_node_t stack_node_t;

typedef clist_t stack_t;


/* Stack public methods */

#define create_stack() ((stack_t *) create_clist(void))

#define init_stack(stack) init_clist((clist_t *) (stack))

#define clear_stack(stack, destroy_data) clear_clist((clist_t *) (stack), destroy_data)

#define destroy_stack(stack, destroy_data) destroy_clist((clist_t *) (stack), destroy_data)

void * get_stack_data(stack_t * stack);

stack_node_t * pop_node(stack_t * stack);

bool put_stack_data(stack_t * stack, const void * data);

void push_node(stack_t * stack, stack_node_t * new_node);

#define peek_stack(stack) ((stack)->head == NULL ? NULL: (stack)->head->data)

#define stack_size(stack) (stack)->size

#endif