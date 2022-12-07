//
// Created by potato_coder on 07.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H
#define SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H

#include <malloc.h>

typedef struct singly_linked_node {
    void *value;
    struct singly_linked_node *next;
} singly_linked_node;

singly_linked_node *singly_linked_node_constructor();

singly_linked_node *singly_linked_list_get_last(singly_linked_node *node, singly_linked_node *prev_node);

singly_linked_node * pop(singly_linked_node *node);//TODO сделать pop и push, чтобы использовать как стек

int * push(singly_linked_node *node);

void singly_linked_list_add_last(singly_linked_node *node, void *value);//TODO сделать возвращение инта, чтобы ловить ошибки

void singly_linked_list_add_first(singly_linked_node **node, void *value);

size_t singly_linked_list_get_size(singly_linked_node* node);

singly_linked_node * singly_linked_list_get(singly_linked_node *node, size_t index);

#endif //SYNTACORE_TOOLS_INTERN_TASK_SINGLY_LINKED_LIST_H
