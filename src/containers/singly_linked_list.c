//
// Created by potato_coder on 07.12.22.
//


//TODO доделать все методы и перепроверить всё!!!
#include "../../include/singly_linked_list.h"

linked_list *linked_list_node_constructor() {
    linked_list *list = malloc(sizeof(void *));
    if (list != NULL) {
        list->next = NULL;
    }
    return list;
}

linked_list *linked_list_init(void *value) {
    linked_list *list = malloc(sizeof(void *));
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

int linked_list_add_last(linked_list *node, void *value) {
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

int linked_list_add_first(linked_list **node, void *value) {
    linked_list *new_node = linked_list_node_constructor();
    if (new_node == NULL) {
        list_destroy(new_node);
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
    if (node == NULL) {
        return -1;
    }
    size_t index = 1;
    while (node != NULL) {
        index += 1;
        node = node->next;
    }
    return index;
}

void *linked_list_get(linked_list *node, size_t index) {
    size_t list_size = linked_list_get_size(node);
    if (index > list_size) {
        return "NULL-value";
    }
    for (size_t i = 0; i <= index; i++) {
        node = node->next;
    }
    return node->value;
}

void list_destroy(linked_list *list) {
    linked_list *buffer;
    while (list != NULL) {
        buffer = list;
        list = list->next;
        free(buffer);
    }
}

void print_linked_list(FILE *stream, char *mode, linked_list *list) {
    if (stream != NULL && list != NULL && mode != NULL) {
        size_t counter = 0;
        fprintf(stream, "%s", "\n[");
        while (list != NULL) {
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

int linked_list_clone(linked_list *list, linked_list **clone) {
    if (list != NULL) {
        //код копирования связного списка тута

    }
    return -1;
}