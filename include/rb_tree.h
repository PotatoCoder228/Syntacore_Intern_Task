//
// Created by potato_coder on 30.12.22.
//

#ifndef SYNTACORE_TOOLS_INTERN_TASK_RB_TREE_H
#define SYNTACORE_TOOLS_INTERN_TASK_RB_TREE_H

enum rb_tree_color {
    BLACK = 0,
    RED
};

typedef struct rb_tree rb_tree;

rb_tree *rb_tree_get_parent(rb_tree *tree);

rb_tree *rb_tree_get_right(rb_tree *tree);

rb_tree *rb_tree_get_left(rb_tree *tree);

enum rb_tree_color rb_tree_get_color(rb_tree *tree);
int64_t rb_tree_get_key(rb_tree *tree);

void rb_tree_set_parent(rb_tree *tree, rb_tree *p);

void rb_tree_set_right(rb_tree *tree, rb_tree *right);

void rb_tree_set_left(rb_tree *tree, rb_tree *left);

void rb_tree_set_color(rb_tree *tree, enum rb_tree_color color);
void rb_tree_set_key(rb_tree *tree, int64_t key);

rb_tree *new_rb_tree(int64_t key);

void rb_tree_left_rotate(rb_tree **tree, rb_tree *cur_node);

void rb_tree_right_rotate(rb_tree **tree, rb_tree *cur_node);

void rb_tree_insert(rb_tree **tree, rb_tree *z);

#endif //SYNTACORE_TOOLS_INTERN_TASK_RB_TREE_H
