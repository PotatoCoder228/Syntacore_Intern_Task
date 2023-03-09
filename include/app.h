//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_APP_H
#define SYNTACORE_TOOLS_INTERN_TASK_APP_H

#include "exceptions/error_s.h"
#include "containers/containers.h"

int app_start(error_s *error);

bool global_tree_init(int64_t key);

void global_tree_print();

bool global_tree_insert(int64_t key);

int64_t global_tree_k_stat(size_t i);

size_t global_tree_counts_less_than(int64_t k);

void global_tree_destroy();

void global_tree_clear();

void global_tree_delete(int64_t num);

void global_tree_inorder_print(FILE *stream);

size_t global_tree_get_size();

bool global_tree_is_init();

#endif //SYNTACORE_TOOLS_INTERN_TASK_APP_H
