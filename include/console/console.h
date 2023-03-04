//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_CONSOLE_H
#define SYNTACORE_TOOLS_INTERN_TASK_CONSOLE_H

#include <stdbool.h>
#include "../../include/command/command.h"
#include "../exceptions/error_s.h"

bool console(error_s *error);

string_builder *read_line(FILE *stream, error_s *error);

#endif //SYNTACORE_TOOLS_INTERN_TASK_CONSOLE_H
