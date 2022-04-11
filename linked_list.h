#include <stdbool.h>

typedef struct element {void *data; struct element *next;} element;

typedef element *list;

list *create_list();

void insert_at_head(list *list, void *data);

void insert_at_tail(list *list, void *data);

void *delete_from_head(list *list); 

void *delete_from_tail(list *list);

void *delete_from_list(list *list);

void insert_in_order(list *list_, void * data, bool (*compare)(void *value1,void *value2));

void print_list(list list, void (print)(void *data));
