//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_OS_TREE_S_H
#define SYNTACORE_TOOLS_INTERN_TASK_OS_TREE_S_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "cont-common.h"

typedef struct os_tree_s os_tree_s;

os_tree_s *new_os_tree(int64_t key);

os_tree_s *os_tree_search(os_tree_s *root, int64_t key);

os_tree_s *os_tree_predecessor(os_tree_s *x);

os_tree_s *os_tree_successor(os_tree_s *x);

os_tree_s *os_tree_maximum(os_tree_s *root);

os_tree_s *os_tree_minimum(os_tree_s *root);

bool os_tree_delete(os_tree_s **root, int64_t key);

bool os_tree_insert(os_tree_s **root, int64_t object);

void os_tree_set_color(os_tree_s *node, enum tree_color color);

void os_tree_set_key(os_tree_s *node, int64_t key);

size_t os_tree_get_size(os_tree_s *node);

void os_tree_set_size(os_tree_s *node, size_t size);

void os_tree_set_parent(os_tree_s *node, os_tree_s *parent);

void os_tree_set_left(os_tree_s *node, os_tree_s *left);

void os_tree_set_right(os_tree_s *node, os_tree_s *right);

int64_t os_tree_get_key(os_tree_s *node);

enum tree_color os_tree_get_color(os_tree_s *node);

os_tree_s *os_tree_get_parent(os_tree_s *node);

os_tree_s *os_tree_get_left(os_tree_s *node);

os_tree_s *os_tree_get_right(os_tree_s *node);

void os_tree_print(os_tree_s *root, int depth);

void os_tree_print_to(FILE *stream, os_tree_s *root, int depth);

os_tree_s *os_tree_select(os_tree_s *x, size_t i);

size_t os_tree_rank(os_tree_s *root, os_tree_s *x);

size_t os_tree_find_counts_less_than(os_tree_s *root, int64_t num);

void os_tree_destroy(os_tree_s *x);

#endif //SYNTACORE_TOOLS_INTERN_TASK_OS_TREE_S_H
