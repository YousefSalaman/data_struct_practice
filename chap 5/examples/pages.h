#ifndef PAGES_H
#define PAGES_H

#include "../lists.h"

// Object that stores information about pages
typedef struct page 
{
    int number;
    int reference;
} page_t;

/* Public page methods */

page_t * replace_page(clist_node_t * curr_page_node);

#endif