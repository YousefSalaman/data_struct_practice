#ifndef EVENTS_H
#define EVENTS_H

#include "../queue.h"

bool receive_event(queue_t *events, const event_t * event);
bool process_event(queue_t * events, bool (*dispatch)(event_t * event));

#endif