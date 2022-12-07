//
// Created by potato_coder on 07.12.22.
//

#include "singly_linked_list.h"

singly_linked_node *singly_linked_node_constructor() {
    singly_linked_node *node = malloc(sizeof(void *));
    return node;
}

singly_linked_node *singly_linked_list_get_last(singly_linked_node *node, singly_linked_node *prev_node) {
    if (node != NULL) {
        prev_node = node;
        node = node->next;
        return singly_linked_list_get_last(node, prev_node);
    }
    return prev_node;
}

void singly_linked_list_add_last(singly_linked_node *node, void *value) {
    singly_linked_node *new_node = singly_linked_node_constructor();
    new_node->value = value;
    new_node->next = NULL;
    singly_linked_node *buffer;
    node = singly_linked_list_get_last(node, buffer);
    node->next = new_node;
}

void singly_linked_list_add_first(singly_linked_node **node, void *value){
    singly_linked_node *new_node = singly_linked_node_constructor();
    new_node -> value = value;
    new_node->next = NULL;
    singly_linked_node *buffer;
    if((*node) ->value!=NULL){
        buffer = new_node;
        new_node = *node;
        *node = buffer;
        (*node)->next = new_node;
    }
    else{
        *node = new_node;
    }
}

size_t singly_linked_list_get_size(singly_linked_node* node){
    size_t index = 1;
    while(node != NULL){
        index += 1;
        node = node -> next;
    }
    return index;
}

singly_linked_node * singly_linked_list_get(singly_linked_node *node, size_t index){
    size_t list_size = singly_linked_list_get_size(node);
    if(index > list_size){
        return NULL;
    }
    while(index > 0){
        index -= 1;
        node = node -> next;
    }
    return node;
}