#ifndef PAGES_H
#define PAGES_H

#include "../lists.h"

// Object that stores information about pages
typedef struct Page_ {
    int number;
    int reference;
} Page;

/* Public page methods */

Page * replace_page(CListNode * curr_page_node);

#endif