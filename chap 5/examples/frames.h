#ifndef FRAMES_H
#define FRAMES_H

/* Public frame methods */

#include "../lists.h"

int alloc_frame(list_t * frames);
bool free_frame(list_t * frames, int frame_num);

#endif