//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_STRING_BUILDER_H
#define SYNTACORE_TOOLS_INTERN_TASK_STRING_BUILDER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <bits/types/FILE.h>
#include "../containers/vector_s.h"

typedef struct string_builder string_builder;

string_builder *new_string_builder();

void string_builder_set_string(string_builder *string_builder, const char *new_string);

char *string_builder_get_string(string_builder *builder);

char *string_builder_to_string(void *string_builder);

void string_builder_copy(string_builder *src, string_builder *dest);

void string_builder_destroy(void *builder);

vector_s *string_builder_get_tokens(string_builder *string, char *sep);

bool string_builder_concat(string_builder *main, string_builder *from);

int string_builder_equals(string_builder *builder_1, string_builder *builder_2);


#endif //SYNTACORE_TOOLS_INTERN_TASK_STRING_BUILDER_H
