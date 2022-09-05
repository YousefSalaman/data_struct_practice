#ifndef STACK_H
#define STACK_H

#include "../chap 5/lists.h"

/* Stack objects */

typedef list_t queue_t;


/* Stack public methods */

#define create_queue() ((queue_t *) create_list(void))

#define init_queue(queue) init_list((list_t *) queue)

#define destroy_queue(queue, destroy_data) destroy_list((list_t *) queue, destroy_data)

#define get_queue_data(queue) delete_list_node((list_t *) queue, NULL)

#define dequeue_node(queue) remove_list_node((list_t *) queue, NULL)

#define put_queue_data(queue, data) add_list_node((list_t *) queue, (queue)->tail, data)

#define enqueue_node(queue, new_node) insert_list_node((list_t *) queue, (queue)->tail, new_node)

#define peek_queue(queue) ((queue)->head == NULL ? NULL: (queue)->head->data)

#define queue_size(queue) (queue)->size

#endif