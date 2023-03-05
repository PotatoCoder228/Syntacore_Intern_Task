//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_ERROR_S_H
#define SYNTACORE_TOOLS_INTERN_TASK_ERROR_S_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "../string/string_builder.h"

enum system_error_codes {
    MEM_ALLOC_DENIED = 900,
    INPUT_STREAM_READ_ERROR,
    NULL_PTR_ERROR
};

typedef struct error_s error_s;

error_s *new_error();

void error_set_message(error_s *error, string_builder *message);

string_builder *error_get_message(error_s *error);

void error_set_code(error_s *error, int code);

int error_get_code(error_s *error);

char *error_to_string(void *error);

void error_print_to(FILE *stream, error_s *error);

void error_print(error_s *error);

void throw_exception(error_s *error, int code, char *message);

void error_destroy(void *error);

void error_set_default(error_s *error);

#endif //SYNTACORE_TOOLS_INTERN_TASK_ERROR_S_H
