//
// Created by sasha on 04.03.2023.
//

#include "../../include/containers/os_tree_s.h"

/**
 * Задача: реализовать красно-черное самобалансирующееся дерево
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
 * (m i) - поиск элемента с индексом i, в порядке возрастания
 * (n j) - поиск количества элементов, меньшего, чем заданный j
 * */


typedef struct os_tree_s {
    int8_t color;
    int64_t key;
    size_t size;
    os_tree_s *p;
    os_tree_s *left;
    os_tree_s *right;
} os_tree_s;


static os_tree_s nil = {.p = NULL, .left = NULL, .right = NULL, .key = 0, .color = BLACK, .size = 0};
static os_tree_s *EMPTY_TREE_NODE = &nil;

os_tree_s *new_os_tree(int64_t key) {
    nil.p = EMPTY_TREE_NODE;
    nil.left = EMPTY_TREE_NODE;
    nil.right = EMPTY_TREE_NODE;
    os_tree_s *new_tree = malloc(sizeof(os_tree_s));
    if (new_tree) {
        new_tree->color = BLACK;
        new_tree->p = EMPTY_TREE_NODE;
        new_tree->left = EMPTY_TREE_NODE;
        new_tree->right = EMPTY_TREE_NODE;
        new_tree->key = key;
        new_tree->size = 1;
    }
    return new_tree;
}

os_tree_s *new_os_tree_node(int64_t key) {
    os_tree_s *new_tree = malloc(sizeof(os_tree_s));
    if (new_tree) {
        new_tree->color = BLACK;
        new_tree->p = EMPTY_TREE_NODE;
        new_tree->left = EMPTY_TREE_NODE;
        new_tree->right = EMPTY_TREE_NODE;
        new_tree->key = key;
        new_tree->size = 1;
    }
    return new_tree;
}

bool os_node_is_empty(os_tree_s *root) {
    return (root == NULL || root == EMPTY_TREE_NODE);
}

/*
 * Деструктор
 * */

void os_destroy(void *node) {
    if (!os_node_is_empty(node)) {
        os_destroy(((os_tree_s *) node)->right);
        os_destroy(((os_tree_s *) node)->left);
        free(node);
    }
}

void os_set_size(os_tree_s *node, size_t size) {
    if (!os_node_is_empty(node)) node->size = size;
}

void os_set_color(os_tree_s *node, int8_t color) {
    if (!os_node_is_empty(node)) node->color = color;
}

void os_set_key(os_tree_s *node, int64_t key) {
    if (!os_node_is_empty(node)) node->key = key;
}

void os_set_parent(os_tree_s *node, os_tree_s *parent) {
    if (!os_node_is_empty(node)) node->p = parent;
}

void os_set_left(os_tree_s *node, os_tree_s *left) {
    if (!os_node_is_empty(node)) node->left = left;
}

void os_set_right(os_tree_s *node, os_tree_s *right) {
    if (!os_node_is_empty(node)) node->right = right;
}

size_t os_size(os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        return node->size;
    }
    return 0;
}

int64_t os_key(os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        return node->key;
    }
    return 0;
}

int8_t os_color(os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        return node->color;
    }
    return BLACK;
}

os_tree_s *os_parent(os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        return node->p;
    }
    return NULL;
}

os_tree_s *os_left(os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        return node->left;
    }
    return NULL;
}

os_tree_s *os_right(os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        return node->right;
    }
    return NULL;
}

void os_print(os_tree_s *root, int depth) {
    if (!os_node_is_empty(root)) {
        os_print(root->right, depth + 1);
        if (depth == 0) {
            printf("----%ld(color:%d, size:%ld)\n", root->key, root->color, root->size);
        } else if (root->p->right == root) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("/---%ld(color:%d, size:%ld)\n", root->key, root->color, root->size);
        } else if (root->p->left == root) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("\\---%ld(color:%d, size:%ld)\n", root->key, root->color, root->size);
        }
        os_print(root->left, depth + 1);
    }
}

os_tree_s *os_search(os_tree_s *node, int64_t target) {
    if (os_node_is_empty(node) || target == node->key) {
        return node;
    }
    if (target < node->key) {
        return os_search(node->left, target);
    } else {
        return os_search(node->right, target);
    }
}

os_tree_s *os_max(os_tree_s *node) {
    while (!os_node_is_empty(node->right)) {
        node = node->right;
    }
    return node;
}

os_tree_s *os_min(os_tree_s *node) {
    while (!os_node_is_empty(node->left)) {
        node = node->left;
    }
    return node;
}

os_tree_s *os_successor(os_tree_s *node) {
    if (!os_node_is_empty(node->right)) {
        return os_min(node->right);
    }
    os_tree_s *buf = node->p;
    while (!os_node_is_empty(buf) && node == buf->right) {
        node = buf;
        buf = buf->p;
    }
    return buf;
}

os_tree_s *os_predecessor(os_tree_s *node) {
    if (!os_node_is_empty(node->left)) {
        return os_max(node->left);
    }
    os_tree_s *buf = node->p;
    while (!os_node_is_empty(buf) && node == buf->left) {
        node = buf;
        buf = buf->p;
    }
    return buf;
}

static void os_left_rotate(os_tree_s **root, os_tree_s *x) {
    os_tree_s *y = x->right;
    x->right = y->left;
    if (!os_node_is_empty(y->left)) {
        y->left->p = x;
    }
    y->p = x->p;
    if (os_node_is_empty(x->p)) {
        *root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else x->p->right = y;
    y->left = x;
    x->p = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

static void os_right_rotate(os_tree_s **root, os_tree_s *x) {
    os_tree_s *y = x->left;
    x->left = y->right;
    if (!os_node_is_empty(y->right)) {
        y->right->p = x;
    }
    y->p = x->p;
    if (os_node_is_empty(x->p)) {
        *root = y;
    } else if (x == x->p->right) {
        x->p->right = y;
    } else x->p->left = y;
    y->right = x;
    x->p = y;
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
}

static void os_insert_fix(os_tree_s **root, os_tree_s *node) {
    os_tree_s *y;
    while (node->p->color == RED) {
        if (node->p == node->p->p->left) {
            y = node->p->p->right;
            if (y->color == RED) {
                node->p->color = BLACK;
                y->color = BLACK;
                node->p->p->color = RED;
                node = node->p->p;
            } else {
                if (node == node->p->right) {
                    node = node->p;
                    os_left_rotate(root, node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                os_right_rotate(root, node->p->p);
            }
        } else {
            y = node->p->p->left;
            if (y->color == RED) {
                node->p->color = BLACK;
                y->color = BLACK;
                node->p->p->color = RED;
                node = node->p->p;
            } else {
                if (node == node->p->left) {
                    node = node->p;
                    os_right_rotate(root, node);
                }
                node->p->color = BLACK;
                node->p->p->color = RED;
                os_left_rotate(root, node->p->p);
            }
        }
    }
    (*root)->color = BLACK;
}

bool os_insert(os_tree_s **root, os_tree_s *z) {
    if (root != NULL) {
        if (*root == NULL || z == NULL) return false;
        os_tree_s *x = *root;
        os_tree_s *y = EMPTY_TREE_NODE;
        while (!os_node_is_empty(x)) {
            x->size++;
            y = x;
            if (z->key < x->key) x = x->left;
            else x = x->right;
        }
        z->p = y;
        if (os_node_is_empty(y)) {
            *root = z;
        } else if (z->key < y->key) y->left = z;
        else y->right = z;
        z->left = EMPTY_TREE_NODE;
        z->right = EMPTY_TREE_NODE;
        z->color = RED;
        os_insert_fix(root, z);
        return true;
    }
    return false;
}

static void os_transplant(os_tree_s **root, os_tree_s *u, os_tree_s *v) {
    if (os_node_is_empty(u->p)) {
        *root = v;
    } else if (u == u->p->left) {
        u->p->left = v;
    } else u->p->right = v;
    v->p = u->p;
}

static void os_delete_fix(os_tree_s **root, os_tree_s *x) {
    while (x != *root && x->color == BLACK) {
        os_tree_s *w;
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                os_left_rotate(root, x->p);
                w = x->p->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    os_right_rotate(root, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                os_left_rotate(root, x->p);
                x = *root;
            }
        } else {
            w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                os_right_rotate(root, x->p);
                w = x->p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    os_left_rotate(root, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                os_right_rotate(root, x->p);
                x = *root;
            }
        }
    }
    x->color = BLACK;
}

bool os_delete(os_tree_s **root, os_tree_s *z) {
    if (!os_node_is_empty(*root) && !os_node_is_empty(z)) {
        os_tree_s *x;
        os_tree_s *y = z;
        int8_t y_original_color = y->color;
        if (os_node_is_empty(z->left)) {
            x = z->right;
            os_transplant(root, z, z->right);
        } else if (os_node_is_empty(z->right)) {
            x = z->left;
            os_transplant(root, z, z->left);
        } else {
            y = os_min(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y != z->right) {
                os_transplant(root, y, y->right);
                y->right = z->right;
                y->right->p = y;
            } else x->p = y;
            os_transplant(root, z, y);
            y->left = z->left;
            y->left->p = y;
            y->color = z->color;
            y->size = z->size;
        }
        os_tree_s *buf = x;
        while (buf != *root) {
            if (!os_node_is_empty(buf)) {
                buf->size--;
            }
            buf = buf->p;
        }
        if (!os_node_is_empty(buf)) {
            buf->size--;
        }
        if (y_original_color == BLACK) {
            os_delete_fix(root, x);
        }
        free(z);
        return true;
    }
    return false;
}

os_tree_s *os_select(os_tree_s *x, size_t i) {
    if (x != NULL && i > 0) {
        size_t r = x->left->size + 1;
        if (i == r) {
            return x;
        } else if (i < r) {
            return os_select(x->left, i);
        } else {
            return os_select(x->right, i - r);
        }
    }
    return NULL;
}

size_t os_rank(os_tree_s *root, os_tree_s *x) {
    size_t r = x->left->size + 1;
    os_tree_s *y = x;
    while (y != root) {
        if (y == y->p->right) {
            r = r + y->p->left->size + 1;
        }
        y = y->p;
    }
    return r;
}

size_t os_find_less_than(os_tree_s *root, int64_t num) {
    if (!os_node_is_empty(root)) {
        os_tree_s *node = root;
        while (!os_node_is_empty(node) && node->key != num) {
            if (num < node->key) {
                if (os_node_is_empty(node->left)) {
                    while ((node->p->key > num) && node->p != EMPTY_TREE_NODE) {
                        node = node->p;
                    }
                    if (node->key < num) {
                        return os_rank(root, node);
                    }
                    if (node->left->key < num && !os_node_is_empty(node->left)) {
                        node = node->left;
                    } else if (node->p->key < num) {
                        node = node->p;
                    }
                    printf("%ld ", node->key);
                    return os_rank(root, node);
                }
                node = node->left;
            } else {
                if (os_node_is_empty(node->right)) {
                    while ((node->p->key > num) && (node->left->key > num) && node->p != EMPTY_TREE_NODE) {
                        node = node->p;
                    }
                    if (node->key < num) {
                        return os_rank(root, node);
                    }
                    if (node->left->key < num) {
                        node = node->left;
                    } else if (node->p->key < num) {
                        node = node->p;
                    }
                    printf("%ld ", node->key);
                    return os_rank(root, node);
                }
                node = node->right;
            }
        }
        printf("%ld ", node->key);
        return os_rank(root, node) - 1;
    }
    return 0;
}

void os_inorder_print(FILE *stream, os_tree_s *node) {
    if (!os_node_is_empty(node)) {
        os_inorder_print(stream, node->left);
        fprintf(stream, "%ld ", node->key);
        os_inorder_print(stream, node->right);
    }
}

/*
 * Реализация итератора
 */

os_tree_s *os_start(os_tree_s *root) {
    return os_min(root);
}

bool os_has_next(os_tree_s *node) {
    if (!os_node_is_empty(os_successor(node))) {
        return true;
    }
    return false;
}

os_tree_s *os_next(os_tree_s *node) {
    return os_successor(node);
}

os_tree_s *os_end(os_tree_s *root) {
    return os_max(root);
}
