//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_VECTOR_S_H
#define SYNTACORE_TOOLS_INTERN_TASK_VECTOR_S_H

#include "cont-common.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct vector_s vector_s;

vector_s *new_vector();

bool vector_resize(vector_s *vector, size_t capacity);

object_s *vector_get_objects(vector_s *vector);

size_t vector_get_size(vector_s *vector);

size_t vector_get_capacity(vector_s *vector);

bool vector_push(vector_s *vector, object_s object);

object_s vector_pop(vector_s *vector);

bool vector_set(vector_s *vector, object_s object, size_t index);

object_s vector_get(vector_s *vector, size_t index);

bool vector_delete(vector_s *vector, size_t index, void (*destroy)(void *));

void vector_foreach(vector_s *vector, callback f);

void vector_destroy(vector_s *vector, void (*destroyer)(void *));

void vector_print(FILE *stream, vector_s *vector, int (printer)(FILE *, char *mode, void *));

#endif //SYNTACORE_TOOLS_INTERN_TASK_VECTOR_S_H
