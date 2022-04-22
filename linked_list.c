#include <stdlib.h>
#include <stdio.h>
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

void *delete_from_head(list *list_) {
    if (*list_ == NULL)
        return NULL;

    void *data = (*list_)->data;
    list old = *list_;
    *list_ = (*list_)->next;
    free(old);
    return data;
} 

void insert_in_order(list *list_, void * data, bool (*compare)(void *value1,void *value2)) {
    element *new_element = malloc(sizeof(element)); 
    new_element->data = data;
    list *copy = list_;

    if (*list_ == NULL || !compare((*copy)->data, data)) {
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
