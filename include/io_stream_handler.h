//
// Created by potato_coder on 04.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_IO_STREAM_HANDLER_H
#define SYNTACORE_TOOLS_INTERN_TASK_IO_STREAM_HANDLER_H

#include "stddef.h"
#include "singly_linked_list.h"


char *stream_readline(FILE *file);

int parse_instructions_line(FILE *file, linked_list *list);

int console_start();

#endif //SYNTACORE_TOOLS_INTERN_TASK_IO_STREAM_HANDLER_H
