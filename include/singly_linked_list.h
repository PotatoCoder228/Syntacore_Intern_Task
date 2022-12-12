//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H
#define SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H

#include <malloc.h>

typedef struct linked_list {
    void *value;
    struct linked_list *next;
}linked_list;

linked_list *linked_list_init(void* value);

linked_list *linked_list_node_constructor();

void* linked_list_get_last(linked_list *node);

void* linked_list_pop(linked_list *node);

int  linked_list_push(linked_list *node, void* value);

int linked_list_add_last(linked_list *node, void *value);

int linked_list_add_first(linked_list **node, void *value);

size_t linked_list_get_size(linked_list* node);

void* linked_list_get(linked_list *node, size_t index);

void list_destroy(linked_list* list);

int linked_list_clone(linked_list *list, linked_list** clone);

#endif //SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H
