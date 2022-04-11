#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linked_list.h"

list *create_list() {
    list *l = malloc(sizeof(list));
    *l = NULL;
    return l;
}

void insert_at_head(list *list, void *data) {
    element *new_element = malloc(sizeof(element)); 
    new_element->next = *list;
    new_element->data = data;
    *list = new_element;
}

void insert_at_tail(list *list, void *data) {
    element *new_element = malloc(sizeof(element)); 
    new_element->next = NULL;
    new_element->data = data;

    while(*list != NULL)
        list = &((*list)->next);

    *list = new_element;
}

void *delete_from_head(list *list) {
    if (*list == NULL)
        return NULL;

    element *list_element = *list;
    *list = (*list)->next;
    return list_element->data;
} 

/*
int compare(void *value1, void *value2) {
    return ((Event*)value1)->time <= ((Event*)value2)->time;
}
*/

void insert_in_order(list *list_, void * data, bool (*compare)(void *value1,void *value2)) {
    element *new_element = malloc(sizeof(element)); 
    new_element->data = data;
    list *copy = list_;

    if (*list_ == NULL || !compare((*copy)->data, data)) { // insertion at the head 
        new_element->next = *copy;
        *list_ = new_element;
        return;
    }

    copy = &(*list_)->next;

    while(*copy != NULL && compare((*copy)->data, data))
        copy = &(*copy)->next;

    if (*copy != NULL)
        new_element->next = (*copy)->next;

    *copy = new_element;
    
}

void print_list(list list, void (print)(void *data)) {

    while (list->next != NULL){
        print(list->data);
        list = list->next;
        printf(" -> ");
    }

    print(list->data);
    printf("\n");
}

/*
void print_list(list list) {

    while (list != NULL){
        printf("%ld -> ", ((Event*)(list->data))->time);
        list = list->next;
    }

    printf("\n");
}
*/

    /*
int main(int argc, char *argv[])
{

    list *l = create_list();
    Event e1 = {arrival, 5};
    Event e2 = {arrival, 3};
    Event e3 = {arrival, 4};
    Event e4 = {arrival, 0};

    insert_at_head(l, &e1);
    print_list(*l);

    insert_in_order(l, &e2);
    print_list(*l);
    delete_from_head(l);
    print_list(*l);
    //delete_from_head(l);
    insert_in_order(l, &e3);
    print_list(*l);
    //delete_from_head(l);
    insert_at_tail(l, &e4);
    print_list(*l);

    return 0;
}
    */    
