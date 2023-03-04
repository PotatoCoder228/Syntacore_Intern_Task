//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_LIST_S_H
#define SYNTACORE_TOOLS_INTERN_TASK_LIST_S_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../object/object.h"
#include "cont-common.h"

typedef struct list_s list_s;

object_s *list_get_object(list_s *list);

void list_set_object(list_s *list, object_s *object);

list_s *list_get_next(list_s *list);

void list_set_next(list_s *list, list_s *next);

void list_destroy(list_s *list, void (*destroyer)(void *data));

list_s *new_list_node();

list_s *new_list(object_s *object);

list_s *list_get_last_node(list_s *node);

object_s *list_get_last_value(list_s *node);

bool list_push(list_s *node, object_s *object);

object_s *list_pop(list_s *node);

bool list_add_last(list_s *node, object_s *object);

bool list_add_first(list_s **node, object_s *object);

size_t list_get_size(list_s *node);

object_s *list_get(list_s *node, size_t index);

bool list_delete(list_s **list, size_t index, void (*destroyer)(void *data));

bool list_insert(list_s **node, size_t index, object_s *object);

void list_foreach(list_s *list, callback iter_func);

void list_print(list_s *list, char *(to_string)(void *));

void list_print_to(FILE *stream, list_s *list, char *(to_string)(void *));

#endif //SYNTACORE_TOOLS_INTERN_TASK_LIST_S_H
