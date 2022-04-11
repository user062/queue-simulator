#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulation.h"


Clients_Queue *processes_queue;
Events_Queue events_queue;
Server_state server;
time_t t_now, service_time, arrival_time;

float mean_response_time, mean_waiting_time;
long clients_served, new_client_id, number_of_clients;

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
    printf("clients served: %ld\n", clients_served);
    printf("mean response time: %f\n", mean_response_time/clients_served);
    printf("mean waiting time: %f\n", mean_waiting_time/clients_served);
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
    events_queue = *create_events_queue();
    t_now = 0;
    service_time = 5;
    arrival_time = 6;
    number_of_clients = 10000000;
    mean_response_time = 0;
    mean_waiting_time = 0;
    clients_served = 0;
    new_client_id = 0;
    create_event(arrival, t_now);
}


bool detect_overflow() {
    return
        events_queue != NULL &&
        ((Event*)events_queue->data)->type == departure &&
        events_queue->next != NULL &&
        ((Event*)events_queue->next->data)->type == start_service; 
}

int main(int argc, char *argv[])
{
    init();

    if (argc == 2 && strcmp(argv[0], "--help")) {
        printf("Simulator for D/D/1 Queue\n");
        printf("Usage: simulator --help\n");
        printf("Usage: print this message\n");
        printf("Usage: simulator number_of_clients client_arrival_time client_service_time \n");
        printf("Usage: simulator (without arguments, equivalent to simulator 10000000 6 5 ) \n");
        return 0;
    }

    if (argc == 3) {
        printf("Simulator for D/D/1 Queue\n");
        printf("missing arguments\n");
        printf("Usage: simulator --help\n");
        printf("Usage: print the help message\n");
        printf("Usage: simulator number_of_clients client_arrival_time client_service_time \n");
        printf("Usage: simulator (without arguments, equivalent to simulator 10000000 6 5 ) \n");
        return 0;
    }

    else if (argc == 4) {
        number_of_clients = strtol(argv[1], NULL, 10);
        arrival_time = strtol(argv[2], NULL, 10);
        service_time = strtol(argv[3], NULL, 10);
        
    }

    Event *event;
    Client *client;

    while (clients_served < number_of_clients) {
        print_events_queue(events_queue);
        print_clients_queue(*processes_queue);
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

