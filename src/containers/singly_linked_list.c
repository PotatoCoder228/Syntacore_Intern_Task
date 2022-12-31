//
// Created by potato_coder on 07.12.22.
//
#include <stdlib.h>
#include "stdio.h"
#include "../../include/singly_linked_list.h"

typedef struct linked_list {
    void *value;
    struct linked_list *next;//8+8+1+(1)=18
} linked_list;

void *linked_list_get_node_value(linked_list *list) {
    return list->value;
}

void linked_list_set_node_value(linked_list *list, void *value) {
    list->value = value;
}

linked_list *linked_list_get_node_next(linked_list *list) {
    return list->next;
}

void linked_list_set_node_next(linked_list *list, linked_list *next) {
    list->next = next;
}

void linked_list_destroy_all_values(linked_list *list) {
    void *value;
    while (list != NULL) {
        value = list->value;
        list = list->next;
        free(value);
    }
}

void linked_list_destroy(linked_list *list, int values_is_alloc) {
    if (values_is_alloc == 1) {
        linked_list_destroy_all_values(list);
    }
    linked_list *buffer;
    while (list != NULL) {
        buffer = list;
        list = list->next;
        free(buffer);
    }
}

linked_list *linked_list_node_constructor() {
    linked_list *list = malloc(sizeof(linked_list));
    if (list != NULL) {
        list->next = NULL;
    }
    return list;
}

linked_list *linked_list_init(void *value) {
    linked_list *list = malloc(sizeof(linked_list));
    if (list != NULL) {
        list->value = value;
        list->next = NULL;
    }
    return list;
}

linked_list *get_last_node(linked_list *node) {//OK
    if (node != NULL) {
        linked_list *prev_node = node;
        while (node != NULL) {
            prev_node = node;
            node = node->next;
        }
        return prev_node;
    }
    return NULL;
}

void *linked_list_get_last(linked_list *node) {//OK
    if (node != NULL) {
        linked_list *prev_node = node;
        while (node != NULL) {
            prev_node = node;
            node = node->next;
        }
        return prev_node->value;
    }
    return NULL;
}

int linked_list_push(linked_list *node, void *value) {//OK
    if (node != NULL) {
        node = get_last_node(node);
        if (node == NULL) {
            return -1;
        }
        linked_list *add_node = linked_list_node_constructor();
        add_node->value = value;
        node->next = add_node;
        return 0;
    }
    return -1;
}

void *linked_list_pop(linked_list *node) {//OK
    if (node != NULL) {
        linked_list *prev_node = node;
        linked_list *last_node = node;
        while (node != NULL) {
            prev_node = last_node;
            last_node = node;
            node = node->next;
        }
        prev_node->next = NULL;
        void *value = last_node->value;
        free(last_node);
        return value;
    }
    return NULL;
}

int linked_list_add_last(linked_list *node, void *value) {//OK
    if (node != NULL) {
        node = get_last_node(node);
        if (node == NULL) {
            return -1;
        }
        linked_list *add_node = linked_list_node_constructor();
        add_node->value = value;
        node->next = add_node;
        return 0;
    }
    return -1;
}

int linked_list_add_first(linked_list **node, void *value) {//OK
    linked_list *new_node = linked_list_node_constructor();
    if (new_node == NULL) {
        linked_list_destroy(new_node, 0);
        return -1;
    }
    new_node->value = value;
    new_node->next = NULL;
    linked_list *buffer;
    if ((*node)->value != NULL) {
        buffer = new_node;
        new_node = *node;
        *node = buffer;
        (*node)->next = new_node;
    } else {
        *node = new_node;
    }
    return 0;
}

size_t linked_list_get_size(linked_list *node) {
    size_t counter = 1;
    while (node != NULL) {
        counter += 1;
        node = node->next;
    }
    return counter;
}

void *linked_list_get(linked_list *node, size_t index) {
    size_t list_size = linked_list_get_size(node);
    if (index > list_size) {
        return NULL;
    }
    for (size_t i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

int linked_list_insert(linked_list **node, size_t index, void *value) {
    size_t list_size = linked_list_get_size(*node);
    if (index > list_size) {
        return -1;
    }
    if (index == 0) {
        linked_list *new_node = linked_list_node_constructor();
        new_node->value = value;
        new_node->next = *node;
        *node = new_node;
        return 0;
    }
    linked_list *new_node = linked_list_node_constructor();
    new_node->value = value;
    for (size_t i = 1; i < index; i++) {
        *node = (*node)->next;
    }
    new_node->next = (*node)->next;
    (*node)->next = new_node;
    return 0;
}

void print_linked_list(FILE *stream, char *mode, linked_list *list) {//OK
    fflush_unlocked(stdout);
    if (stream != NULL && list != NULL && mode != NULL) {
        size_t counter = 0;
        fprintf(stream, "%s", "\n[");
        while (list != NULL) {
            rewind(stdout);
            fprintf(stream, mode, list->value);
            counter += 1;
            list = list->next;
            if (list != NULL) {
                fprintf(stream, "%s", ", ");
            }
            if (counter % 10 == 0) {
                fprintf(stream, "%s", "\n");
            }
        }
        fprintf(stream, "%s", "]\n");
    }
}

int linked_list_clone(linked_list *list, linked_list **clone) {//TODO дописать клонирование и итератор по списку
    if (list != NULL) {
        //код копирования связного списка тута

    }
    return -1;
}