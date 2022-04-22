#include <time.h>
#include "clients_queue.h"
#include "events_queue.h"

typedef enum Server_state {busy, idle} Server_state;

void init();

void create_event(Event_type type, float time);

void delete_event(Event *event);

Event *get_event();

void process_arrival();

Client *process_start_service();

void process_departure(Client *client);

void print_statistics();

Client *create_client();

float arrival_time();
