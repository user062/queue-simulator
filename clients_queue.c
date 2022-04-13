#include <stdlib.h>
#include <stdio.h>
#include "clients_queue.h"

Clients_Queue *create_clients_queue() {
    Clients_Queue *queue = malloc(sizeof(Clients_Queue));
    queue->size = 0;
    queue->head = queue->tail = NULL;
    return queue;
}

void client_enqueue(Clients_Queue *queue, Client *element) {
    Clients_Queue_element *queue_element = malloc(sizeof(Clients_Queue_element));
    queue_element->value = element;
    queue_element->next = queue->head;
    queue->head = queue_element;
    queue->size++;

    if (queue->size == 1)
        queue->tail = queue->head;
}

Client *client_dequeue(Clients_Queue *queue) {
    Client *client = (queue->tail)->value;
    Clients_Queue_element *new_tail = queue->head;

    if (queue->size == 1) {
        queue->head = queue->tail = NULL;
        queue->size = 0;
        return client;
    }

    for (int i = 1; i < queue->size - 1; i++)
        new_tail = new_tail->next;

    new_tail->next = NULL;
    queue->tail = new_tail;
    queue->size--;

    return client;
}

void print_clients_queue(Clients_Queue queue) {
    Clients_Queue_element *c = queue.head;
    printf("Clients: ");

    if(c == NULL){
        printf("empty\n");
        return;
    }

    while(c->next != NULL) {
        printf("{id:%d, arrival_time:%ld, start_service:%ld} -> ", c->value->id, c->value->t_arrival, c->value->t_start_service);
        c = c->next;
    }

    printf("{id:%d, arrival_time:%ld, start_service:%ld}\n", c->value->id, c->value->t_arrival, c->value->t_start_service);
}
