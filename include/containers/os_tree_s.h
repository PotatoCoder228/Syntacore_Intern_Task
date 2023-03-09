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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "stdlib.h"

typedef struct os_tree_s os_tree_s;

os_tree_s *new_os_tree(int64_t key);

os_tree_s *new_os_tree_node(int64_t key);

bool os_node_is_empty(os_tree_s *root);

void os_destroy(void *node);

void os_set_size(os_tree_s *node, size_t size);

void os_set_color(os_tree_s *node, int8_t color);

void os_set_key(os_tree_s *node, int64_t key);

void os_set_parent(os_tree_s *node, os_tree_s *parent);

void os_set_left(os_tree_s *node, os_tree_s *left);

void os_set_right(os_tree_s *node, os_tree_s *right);

size_t os_size(os_tree_s *node);

int64_t os_key(os_tree_s *node);

int8_t os_color(os_tree_s *node);

os_tree_s *os_parent(os_tree_s *node);

os_tree_s *os_left(os_tree_s *node);

os_tree_s *os_right(os_tree_s *node);

void os_print(os_tree_s *root, int depth);

os_tree_s *os_search(os_tree_s *node, int64_t target);

os_tree_s *os_max(os_tree_s *node);


os_tree_s *os_min(os_tree_s *node);

os_tree_s *os_successor(os_tree_s *node);

os_tree_s *os_predecessor(os_tree_s *node);

bool os_insert(os_tree_s **root, os_tree_s *z);

bool os_delete(os_tree_s **root, os_tree_s *z);

os_tree_s *os_select(os_tree_s *x, size_t i);

size_t os_rank(os_tree_s *root, os_tree_s *x);

size_t os_find_less_than(os_tree_s *root, int64_t num);

void os_inorder_print(FILE *stream, os_tree_s *node);

#endif //SYNTACORE_TOOLS_INTERN_TASK_OS_TREE_S_H
