#include <time.h>
#include "linked_list.h"

typedef enum Event_type {arrival, start_service, departure} Event_type;

typedef struct Event {Event_type type; time_t time;} Event;

typedef list Events_Queue;


Events_Queue *create_events_queue();

void event_enqueue(Events_Queue *queue, Event *element);

Event *event_dequeue(Events_Queue *queue);

bool compare(void *value1, void *value2);

void print_event(void *event);

void print_events_queue(Events_Queue queue);
