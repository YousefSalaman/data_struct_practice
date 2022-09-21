#include <stdlib.h>
#include <string.h>

#include "event.h"
#include "events.h"
#include "../queue.h"


bool receive_event(queue_t *events, const event_t * event)
{
    event_t * new_event;

    if ((new_event = malloc(sizeof(event_t))) == NULL)
    {
        return false;
    }

    memcpy(new_event, event, sizeof(event_t));

    if (enqueue_node(events, event))
    {
        return false;
    }

    return true;
}


bool process_event(queue_t * events, bool (*dispatch)(event_t * event))
{
    event_t * event;

    if (queue_size(events) == 0 || (event = dequeue_node(events)) != NULL)
    {
        return false;
    }
    
    dispatch(event);
    free(event);

    return true;
}