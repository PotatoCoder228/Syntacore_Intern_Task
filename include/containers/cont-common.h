//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_CONT_COMMON_H
#define SYNTACORE_TOOLS_INTERN_TASK_CONT_COMMON_H
enum tree_color {
    BLACK = 0,
    RED
};

enum vector_consts {
    VECTOR_INIT_CAPACITY = 10
};

typedef void *(*callback)(void *data);

#endif //SYNTACORE_TOOLS_INTERN_TASK_CONT_COMMON_H
