#include <stdlib.h>

#include "../lists.h"
#include "frames.h"


int alloc_frame(list_t * frames)
{
    int * data;
    int frame_num;

    // If no frames available or frame could not be retrieved
    if (frames->size == 0 || (data = remove_next_list_node(frames, NULL)) == NULL)
    {
        return -1;
    }

    // Pass the available frame number
    frame_num = *data;
    free(data);

    return frame_num;
}


bool free_frame(list_t * frames, int frame_num)
{
    int * data;

    // If data could not be allocated nor inserted
    if (data = malloc(sizeof(int)) == NULL || !insert_next_list_node(frames, NULL, data))
    {
        if (data != NULL)  // Data could not be inserted
        {
            free(data);
        }
        return false;
    }

    *data = frame_num;
    return true;
    
}