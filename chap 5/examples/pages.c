#include "pages.h"


page_t * replace_page(clist_node_t * curr_page_node)
{
    page_t * curr_page = curr_page_node->data;

    while (curr_page->reference != 0)
    {
        curr_page->reference = 1;
        curr_page = list_next(curr_page_node);
    }

    return curr_page;
}