#include <time.h>

typedef struct Client {int id; time_t t_arrival; time_t t_start_service; time_t service_time;} Client;

typedef struct Clients_Queue_element_ {Client *value; struct Clients_Queue_element_ *next;} Clients_Queue_element;

typedef struct {Clients_Queue_element *head; Clients_Queue_element *tail; int size;} Clients_Queue;

Clients_Queue *create_clients_queue();

void client_enqueue(Clients_Queue *queue, Client *element);

Client *client_dequeue(Clients_Queue *queue);
