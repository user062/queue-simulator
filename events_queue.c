#include <stdlib.h>
#include "events_queue.h"

Events_Queue *create_events_queue() {
    Events_Queue *queue = malloc(sizeof(Events_Queue));
    queue->next = queue->previous = NULL;
    queue->value = NULL;
    return queue;
}

void event_enqueue(Events_Queue **queue, Event *element) {
    // insertion when empty
    if ((*queue)->previous == NULL && (*queue)->next == NULL && (*queue)->value == NULL) {
        (*queue)->value = element;
        return;
    }

    Events_Queue_element *queue_element = malloc(sizeof(Events_Queue_element));
    queue_element->value = element;
    Events_Queue *copy = *queue;

    while (copy->value->time <= element->time && copy->next != NULL)
        copy = copy->next;


    // insertion at the beginning
    if (copy->previous == NULL && element->time < copy->value->time) {
        queue_element->previous = NULL;
        queue_element->next = *queue;
        (*queue)->previous = queue_element;
        *queue = queue_element;
        return;
    } 

    //insertion at the end
    if (copy->next == NULL && copy->value->time <= element->time) {
        queue_element->previous = copy;
        queue_element->next = NULL;
        copy->next = queue_element;
        return;
    }

    // insertion in the middle
    queue_element->previous = copy->previous;
    queue_element->next = copy;
    copy->previous = queue_element;
    return;
}

Event *event_dequeue(Events_Queue **queue) {
    Event *event = (*queue)->value;

    if((*queue)->next == NULL) {
        (*queue)->previous = NULL;
        (*queue)->value = NULL;
    }

    else {
        *queue = (*queue)->next;
        (*queue)->previous = NULL;
    }

    return event;
}
/*

 */
