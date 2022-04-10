#include <time.h>

typedef enum Event_type {arrival, start_service, departure} Event_type;

typedef struct Event {Event_type type; time_t time;} Event;

typedef struct Events_Queue_element_ {
    Event *value;
    struct Events_Queue_element_ *previous;
    struct Events_Queue_element_ *next;} Events_Queue_element;

typedef Events_Queue_element Events_Queue;

Events_Queue *create_events_queue();

void event_enqueue(Events_Queue **queue, Event *element);

Event *event_dequeue(Events_Queue **queue);
