//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_IO_HANDLER_H
#define SYNTACORE_TOOLS_INTERN_TASK_IO_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "../exceptions/error_s.h"

enum open_file_modes {
    R = 0,
    W,
    A,
    RB,
    WB,
    AB,
    R_EXTENDED,
    W_EXTENDED,
    A_EXTENDED,
    RB_EXTENDED,
    WB_EXTENDED,
    AB_EXTENDED,
    RT,
    WT,
    AT,
    RT_EXTENDED,
    WT_EXTENDED,
    AT_EXTENDED
};

enum open_modes_counts {
    MODES_COUNTS = 18
};

static char *open_file_modes[MODES_COUNTS] = {
        "r", "w", "a", "rb", "wb", "ab",
        "r+", "w+", "a+", "r+b", "w+b",
        "a+b", "rt", "wt", "at", "r+t",
        "w+t", "a+t"
};

void open_file(FILE **stream, char *filename, enum open_file_modes mode, error_s *error);

void close_file(FILE **stream, error_s *error);

#endif //SYNTACORE_TOOLS_INTERN_TASK_IO_HANDLER_H
