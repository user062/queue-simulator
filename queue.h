typedef int Type;

typedef struct Queue_element {Type value; struct Queue_element *next;} Queue_element;

typedef struct Queue {Queue_element *head; Queue_element *tail; int size;} *Queue;

Queue create_queue();

void enqueue(Queue queue, Type element);

Type dequeue(Queue queue);

void print_queue(Queue queue);
