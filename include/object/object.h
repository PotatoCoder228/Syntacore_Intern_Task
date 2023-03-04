//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_OBJECT_H
#define SYNTACORE_TOOLS_INTERN_TASK_OBJECT_H

#include <stdbool.h>
#include <stdlib.h>

enum object_is {
    NON_IN_HEAP = 0,
    IN_HEAP
};

typedef struct object_s object_s;

object_s *new_object(void *value, enum object_is in_heap);

void *object_get_value(object_s *object);

enum object_is object_get_in_heap(object_s *object);

void object_destroy(object_s *object, void (*destroyer)(void *));

int object_compare(void *first, void *second, int(*compare)(void *, void *));

char *object_to_string(object_s *object, char *to_string(void *));

#endif //SYNTACORE_TOOLS_INTERN_TASK_OBJECT_H
