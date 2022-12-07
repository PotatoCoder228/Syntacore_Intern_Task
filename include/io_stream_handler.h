//
// Created by potato_coder on 04.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_IO_STREAM_HANDLER_H
#define SYNTACORE_TOOLS_INTERN_TASK_IO_STREAM_HANDLER_H

#include "stddef.h"

int read_command(char* buffer, size_t string_size);//TODO сделать чтение команды и чтение режимов по отдельности
int call_main_console();

#endif //SYNTACORE_TOOLS_INTERN_TASK_IO_STREAM_HANDLER_H
