//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_CONSOLE_H
#define SYNTACORE_TOOLS_INTERN_TASK_CONSOLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/command/command.h"
#include "../exceptions/error_s.h"
#include "../containers/containers.h"

user_command *parse_and_set_tree_command(vector_s *vector, size_t index);

bool console(error_s *error);

string_builder *read_line(FILE *stream, error_s *error);

#endif //SYNTACORE_TOOLS_INTERN_TASK_CONSOLE_H
