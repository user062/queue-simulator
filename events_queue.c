#include "events_queue.h"
#include <stdio.h>

Events_Queue *create_events_queue() {
    return create_list();
}

void event_enqueue(Events_Queue *queue, Event *element) {
    insert_in_order(queue, element, compare);
}

bool compare(void *value1, void *value2) {
    if (((Event*)value2)->type == start_service)
        // priority should be given to start_service as it is independent of of arrival
        return ((Event*)value1)->time < ((Event*)value2)->time;

    return ((Event*)value1)->time <= ((Event*)value2)->time;
}

Event *event_dequeue(Events_Queue *queue) {
    return delete_from_head(queue);
}

void print_event(void *event) {
    switch(((Event *)event)->type) {
        case arrival: printf("{arrival, %ld}", (((Event *)event)->time)); break;
        case start_service: printf("{start_service, %ld}", ((Event *)event)->time); break;
        case departure: printf("{departure, %ld}", ((Event *)event)->time); break;
    }
}

void print_events_queue(Events_Queue queue) {
    print_list(queue, print_event);
}
