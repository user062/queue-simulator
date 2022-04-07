#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

Queue create_queue() {
    Queue queue = malloc(sizeof(Queue));
    return queue;
}

void enqueue(Queue queue, Type element) {
    Queue_element *queue_element = malloc(sizeof(Queue_element));
    queue_element->value = element;
    queue_element->next = queue->head;
    queue->head = queue_element;
    queue->size++;

    if (queue->size == 1)
        queue->tail = queue->head;
}

Type dequeue(Queue queue) {
    Type value = queue->tail->value;
    Queue_element new_tail = *(queue->head);

    for (int i = 1; i < queue->size - 1; i++)
        new_tail = *(new_tail.next);

    free(queue->tail);
    new_tail.next = NULL;
    *(queue->tail) = new_tail;
    queue->size--;

    return value;
}

void print_queue(Queue queue) { // This should be refactored to be generic (Type agnostic)
    Queue_element element = *queue->head;

    for (int i = 0; i < queue->size - 1; i++) {
        printf("%d -> ", element.value);
        element = *element.next;
    }

    printf("%d\n", element.value);
}

int main(int argc, char *argv[])
{
    Type t[] = {1,2,3,4,5};
    Queue queue = create_queue();

    for (int i = 0; i < 5; i++)
        enqueue(queue, t[i]);


    print_queue(queue);
    assert(dequeue(queue) == 1);
    assert(dequeue(queue) == 2);
    print_queue(queue);

    return 0;
}
