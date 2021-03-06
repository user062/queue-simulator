#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simulation.h"


Clients_Queue *clients_queue;
Events_Queue *events_queue;
Server_state server;
time_t t_now, service_time, arrival_time;

float mean_response_time, mean_waiting_time;
long clients_served, new_client_id, number_of_clients;

Client *create_client() {
    Client *client = malloc(sizeof(Client));
    client->id = new_client_id++;
    client->t_arrival = t_now;
    client->service_time = service_time;
    return client;
}

void process_arrival() {
    Client *client = create_client();
    client_enqueue(clients_queue, client);

    if (server == idle)
        create_event(start_service, t_now);

    create_event(arrival, t_now+arrival_time);
}

Client *process_start_service() {
    server = busy;
    Client *client = client_dequeue(clients_queue);
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

    if (clients_queue->size > 0)
        create_event(start_service, t_now);
}

void print_statistics() {
    printf("number of clients served: %ld\n", clients_served);
    printf("mean response time: %.3f\n", mean_response_time/clients_served);
    printf("mean waiting time: %.3f\n", mean_waiting_time/clients_served);
    printf("throughput: %.3f\n", (float)clients_served/t_now);
}

Event *get_event() {
    return event_dequeue(events_queue);
}

void create_event(Event_type type, time_t time) {
    Event *event = malloc(sizeof(Event));
    event->type = type;
    event->time = time;
    event_enqueue(events_queue, event);
}

void delete_event(Event *event) {
    free(event);
}

void init() {
    server = idle;
    clients_queue = create_clients_queue();
    events_queue = create_events_queue();
    t_now = 0;
    service_time = 5; // chosen arbitrarily
    arrival_time = 6; // chosen arbitrarily
    number_of_clients = 10000000; // chosen arbitrarily
    mean_response_time = 0;
    mean_waiting_time = 0;
    clients_served = 0;
    new_client_id = 0;
    create_event(arrival, t_now);
}

int main(int argc, char *argv[])
{
    init();


    if (argc == 1) {
        printf("Simulator for D/D/1 Queue\n");
        printf("Usage: simulator --help   print this message\n");
        printf("Usage: simulator number_of_clients client_arrival_time client_service_time \n");
        printf("Usage: simulator --default (equivalent to simulator 10000000 6 5 ) \n");
        return 0;
    }

    if (argc == 2 && !strcmp(argv[1], "--help")) {
        printf("Simulator for D/D/1 Queue\n");
        printf("Usage: simulator --help   print this message\n");
        printf("Usage: simulator number_of_clients client_arrival_time client_service_time \n");
        printf("Usage: simulator --default (equivalent to simulator 10000000 6 5 ) \n");
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--default")) {
        printf("missing or invalid argument\n");
        printf("Usage: simulator --help   print this message\n");
        printf("Usage: simulator number_of_clients client_arrival_time client_service_time \n");
        printf("Usage: simulator --default (equivalent to simulator 10000000 6 5 ) \n");
        return 0;
    }

    if (argc == 3 || argc > 4) {
        printf("missing or invalid arguments\n");
        printf("Usage: simulator --help   print this message\n");
        printf("Usage: simulator number_of_clients client_arrival_time client_service_time \n");
        printf("Usage: simulator --default (equivalent to simulator 10000000 6 5 ) \n");
        return 0;
    }

    if (argc == 4) {
        number_of_clients = strtol(argv[1], NULL, 10);
        arrival_time = strtol(argv[2], NULL, 10);
        service_time = strtol(argv[3], NULL, 10);
    }


    Event *event;
    Client *client;

    while (clients_served < number_of_clients) {
    // could also be changed to exit after a certain amount of time regardless of how many clients were served

        /*
            print_events_queue(*events_queue);
            print_clients_queue(*clients_queue);
            printf("\n");
        */

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

