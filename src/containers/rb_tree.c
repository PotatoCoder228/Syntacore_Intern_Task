//
// Created by potato_coder on 30.12.22.
//

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "../../include/rb_tree.h"

/**
 * Задача: реализовать красно-черное балансирующееся дерево
 * Идея: есть node с цветом, значением(key), родителем(p)
 * и правой и левой ветвью.
 * Свойства:
 * 1) Каждый узел является либо красным, либо чёрным
 * 2) Корень дерева является чёрным узлом
 * 3) Каждый лист дерева == NULL - чёрный
 * 4) Если узел красный, то оба его дочерних узла - чёрные.
 * 5) Для каждого узла, все простые пути от него до листьев,
 * являющихся потомками данного узла, содержат одно
 * и то же количество чёрных узлов;
 *
 * При операциях insert и delete мы должны менять структуру деревьев,
 * поэтому нужны методы поворотов и перекраски узлов.
 *
 *
 * Идея расширенного дерева для k-ной наименьшей статистики: в работе,
 * возможно, стоит сделать наследование от классического rb_tree.
 * */
typedef struct rb_tree {
    enum rb_tree_color color;
    struct rb_tree *p, *left, *right;//p is parent
    int64_t key;
} rb_tree;

rb_tree *new_rb_tree(int64_t key) {
    rb_tree *tree = malloc(sizeof(rb_tree));
    tree->color = BLACK;
    tree->p = NULL;
    tree->left = NULL;
    tree->right = NULL;
    tree->key = key;
    return tree;
}

rb_tree *rb_tree_get_parent(rb_tree *tree) {
    return tree->p;
}

rb_tree *rb_tree_get_right(rb_tree *tree) {
    return tree->right;
}

rb_tree *rb_tree_get_left(rb_tree *tree) {
    return tree->left;
}

enum rb_tree_color rb_tree_get_color(rb_tree *tree) {
    return tree->color;
}

int64_t rb_tree_get_key(rb_tree *tree){
    return tree->key;
}

void rb_tree_set_parent(rb_tree *tree, rb_tree *p) {
    tree->p = p;
}

void rb_tree_set_right(rb_tree *tree, rb_tree *right) {
    tree->right = right;
}

void rb_tree_set_left(rb_tree *tree, rb_tree *left) {
    tree->left = left;
}

void rb_tree_set_color(rb_tree *tree, enum rb_tree_color color) {
    tree->color = color;
}

void rb_tree_set_key(rb_tree *tree, int64_t key){
    tree->key=key;
}

void rb_tree_left_rotate(rb_tree **tree, rb_tree *cur_node) {
    rb_tree *next_node = cur_node->right;
    cur_node->right = next_node->left;

    if (next_node->left != NULL) {
        next_node->left->p = cur_node;
    }

    next_node->p = cur_node->p;

    if (next_node->p == NULL) {
        *tree = next_node;
    } else if ((cur_node->p->left) == cur_node) {
        cur_node->p->left = next_node;
    } else {
        cur_node->p->right = next_node;
    }

    next_node->left = cur_node;
    cur_node->p = next_node;
}

void rb_tree_right_rotate(rb_tree **tree, rb_tree *cur_node) {
    rb_tree *next_node = cur_node->left;
    cur_node->left = next_node->right;

    if (next_node->right != NULL) {
        next_node->right->p = cur_node;
    }

    next_node->p = cur_node->p;

    if (next_node->p == NULL) {
        *tree = next_node;
    } else if ((cur_node->p->left) == cur_node) {
        cur_node->p->left = next_node;
    } else {
        cur_node->p->right = next_node;
    }
    next_node->right = cur_node;
    cur_node->p = next_node;
}

static void rb_tree_insert_fixup(rb_tree **tree, rb_tree *z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            rb_tree *y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else if (z == z->p->right) {
                z = z->p;
                rb_tree_left_rotate(tree, z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            rb_tree_right_rotate(tree, z->p->p);
        } else {
            rb_tree *y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            } else if (z == z->p->left) {
                z = z->p;
                rb_tree_left_rotate(tree, z);
            }
            z->p->color = BLACK;
            z->p->p->color = RED;
            rb_tree_right_rotate(tree, z->p->p);
        }
    }
    (*tree)->color = BLACK;
}

void rb_tree_insert(rb_tree **tree, rb_tree *z) {
    rb_tree *y = NULL;
    rb_tree *x = *tree;
    while (x != NULL) {
        y = x;
        if ((z->key) < (x->key)) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NULL) {
        *tree = z;
    } else if ((z->key) < (y->key)) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = NULL;
    z->right = NULL;
    z->color = RED;
    rb_tree_insert_fixup(tree, z);
}
