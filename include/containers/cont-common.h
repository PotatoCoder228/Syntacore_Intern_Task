//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_CONT_COMMON_H
#define SYNTACORE_TOOLS_INTERN_TASK_CONT_COMMON_H

#include "stdint.h"

static const int8_t BLACK = 0;
static const int8_t RED = 1;

typedef void *object_s;

enum vector_consts {
    VECTOR_INIT_CAPACITY = 10
};

typedef void *(*callback)(void *data);

#endif //SYNTACORE_TOOLS_INTERN_TASK_CONT_COMMON_H
