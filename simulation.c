#include <stdlib.h>
#include <stdio.h>
#include "simulation.h"

#define BIG_NUMBER 10000000

Clients_Queue *processes_queue;
Events_Queue *events_queue;
Server_state server;
time_t t_now, service_time, arrival_time;

float mean_response_time, mean_waiting_time;
int clients_served, new_client_id;

void process_arrival() {
    Client *client = malloc(sizeof(Client));
    client->id = new_client_id++;
    client->t_arrival = t_now;
    client->service_time = service_time;
    client_enqueue(processes_queue, client);

    if (server == idle)
        create_event(start_service, t_now);

    create_event(arrival, t_now+arrival_time);
}

Client *process_start_service() {
    server = busy;
    Client *client = client_dequeue(processes_queue);
    client->t_start_service = t_now;
    create_event(departure, t_now + client->service_time);
    return client;
}

void process_departure(Client *client) {
    server = idle;
    mean_response_time += t_now - client->t_arrival;
    mean_waiting_time += client->t_start_service - client->t_arrival;
    clients_served++;
    free(client);

    if (processes_queue->size > 0)
        create_event(start_service, t_now);
}

void print_statistics() {
    printf("mean_response_time: %f\n", mean_response_time/clients_served);
    printf("mean_waiting_time: %f\n", mean_waiting_time/clients_served);
    printf("throughput: %f\n", (float)clients_served/t_now);
}

Event *get_event() {
    return event_dequeue(&events_queue);
}

void create_event(Event_type type, time_t time) {
    Event *event = malloc(sizeof(Event));
    event->type = type;
    event->time = time;
    event_enqueue(&events_queue, event);
}

void delete_event(Event *event) {
    free(event);
}

void init() {
    server = idle;
    processes_queue = create_clients_queue();
    events_queue = create_events_queue();
    t_now = 0;
    service_time = 5;
    arrival_time = 6;
    mean_response_time = 0;
    mean_waiting_time = 0;
    clients_served = 0;
    new_client_id = 0;
    create_event(arrival, t_now);
}

void print_events() {
    Events_Queue *events = events_queue;

    while(events->next != NULL) {
        switch(events->value->type) {
        case arrival: printf("arrival -> "); break;
        case start_service: printf("start_service -> "); break;
        case departure: printf("departure -> "); break;
        }
        events = events->next;
    }
        switch(events->value->type) {
        case arrival: printf("arrival\n"); break;
        case start_service: printf("start_service\n"); break;
        case departure: printf("departure\n"); break;
        }
}

int main(int argc, char *argv[])
{
    Event *event;
    Client *client;

    init();

    while (clients_served <= BIG_NUMBER) {
        event = get_event();
        t_now = event->time;

        switch (event->type) {
            case arrival: process_arrival(); break;
            case start_service: client = process_start_service(); break;
            case departure: process_departure(client); break;
        }

        delete_event(event);

    }

    print_statistics();

    return 0;
}

