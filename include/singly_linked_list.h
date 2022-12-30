//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H
#define SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H

#include <stdio.h>

typedef struct linked_list linked_list;

void *linked_list_get_node_value(linked_list *list);

void linked_list_set_node_value(linked_list *list, void *value);

linked_list *linked_list_get_node_next(linked_list *list);

void linked_list_set_node_next(linked_list *list, linked_list *next);

linked_list *linked_list_init(void *value);


linked_list *linked_list_node_constructor();

void *linked_list_get_last(linked_list *node);

void *linked_list_pop(linked_list *node);

int linked_list_push(linked_list *node, void *value);

int linked_list_add_last(linked_list *node, void *value);

int linked_list_add_first(linked_list **node, void *value);

size_t linked_list_get_size(linked_list *node);

void *linked_list_get(linked_list *node, size_t index);

void linked_list_destroy(linked_list *list, int values_is_alloc);

int linked_list_clone(linked_list *list, linked_list **clone);

void print_linked_list(FILE *stream, char *mode, linked_list *list);

void linked_list_destroy_all_values(linked_list *list);

int linked_list_insert(linked_list **node, size_t index, void *value);

#endif //SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H
