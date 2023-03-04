//
// Created by sasha on 04.03.2023.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_RB_TREE_S_H
#define SYNTACORE_TOOLS_INTERN_TASK_RB_TREE_S_H

#include <bits/types/FILE.h>
#include <stdio.h>
#include "../object/object.h"
#include "cont-common.h"


typedef struct rb_tree_s rb_tree_s;

rb_tree_s *new_rb_tree(object_s *key);

bool rb_tree_insert(rb_tree_s **root, object_s *key, int compare(void *, void *));

rb_tree_s *rb_tree_search(rb_tree_s *node, object_s *key, int compare(void *, void *));

void rb_tree_set_color(rb_tree_s *node, enum tree_color color);

void rb_tree_set_key(rb_tree_s *node, object_s *key);

void rb_tree_set_parent(rb_tree_s *node, rb_tree_s *parent);

void rb_tree_set_left(rb_tree_s *node, rb_tree_s *left);

void rb_tree_set_right(rb_tree_s *node, rb_tree_s *right);

object_s *rb_tree_get_key(rb_tree_s *node);

enum tree_color rb_tree_get_color(rb_tree_s *node);

rb_tree_s *rb_tree_get_parent(rb_tree_s *node);

rb_tree_s *rb_tree_get_left(rb_tree_s *node);

rb_tree_s *rb_tree_get_right(rb_tree_s *node);

void rb_tree_print(rb_tree_s *node, char *(to_string)(void *), int depth);

void rb_tree_print_to(FILE *stream, rb_tree_s *node, char *(to_string)(void *), int depth);

void rb_tree_destroy(rb_tree_s *node, void (*destroyer)(void *));

#endif //SYNTACORE_TOOLS_INTERN_TASK_RB_TREE_S_H
