#ifndef FRAMES_H
#define FRAMES_H

/* Public frame methods */

int alloc_frame(List * frames);
bool free_frame(List * frames, int frame_num);

#endif