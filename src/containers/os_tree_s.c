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
    size_t size;
    enum tree_color color;
    os_tree_s *p;
    os_tree_s *left;
    os_tree_s *right;
    int64_t key;
} os_tree_s;

void os_tree_set_size(os_tree_s *node, size_t size) {
    if (node != NULL) {
        node->size = size;
    }
}

void os_tree_set_color(os_tree_s *node, enum tree_color color) {
    if (node != NULL) {
        node->color = color;
    }
}

void os_tree_set_key(os_tree_s *node, int64_t key) {
    if (node != NULL) {
        node->key = key;
    }
}

void os_tree_set_parent(os_tree_s *node, os_tree_s *parent) {
    if (node != NULL) {
        node->p = parent;
    }
}

void os_tree_set_left(os_tree_s *node, os_tree_s *left) {
    if (node != NULL) {
        node->left = left;
    }
}

void os_tree_set_right(os_tree_s *node, os_tree_s *right) {
    if (node != NULL) {
        node->right = right;
    }
}

size_t os_tree_get_size(os_tree_s *node) {
    if (node != NULL) {
        return node->size;
    }
    return 0;
}

int64_t os_tree_get_key(os_tree_s *node) {
    if (node != NULL) {
        return node->key;
    }
    return 0;
}

enum tree_color os_tree_get_color(os_tree_s *node) {
    if (node != NULL) {
        return node->color;
    }
    return BLACK;
}

os_tree_s *os_tree_get_parent(os_tree_s *node) {
    if (node != NULL) {
        return node->p;
    }
    return NULL;
}

os_tree_s *os_tree_get_left(os_tree_s *node) {
    if (node != NULL) {
        return node->left;
    }
    return NULL;
}

os_tree_s *os_tree_get_right(os_tree_s *node) {
    if (node != NULL) {
        return node->right;
    }
    return NULL;
}

static os_tree_s nil = {.p = NULL, .left = NULL, .right = NULL, .key = 0, .color = BLACK, .size = 0};
static os_tree_s *T = &nil;

os_tree_s *new_os_tree(int64_t key) {
    nil.p = T;
    nil.left = T;
    nil.right = T;
    os_tree_s *new_tree = malloc(sizeof(os_tree_s));
    if (new_tree) {
        new_tree->color = BLACK;
        new_tree->p = T;
        new_tree->left = T;
        new_tree->right = T;
        new_tree->key = key;
        new_tree->size = 0;
    }
    return new_tree;
}

os_tree_s *new_os_tree_node(int64_t key) {
    os_tree_s *new_tree = malloc(sizeof(os_tree_s));
    if (new_tree) {
        new_tree->color = BLACK;
        new_tree->p = T;
        new_tree->left = T;
        new_tree->right = T;
        new_tree->key = key;
    }
    return new_tree;
}

os_tree_s *os_tree_search(os_tree_s *root, int64_t key) {
    if (root != NULL) {
        if (root == T || key == root->key) {
            return root;
        }
        if (key < root->key) {
            return os_tree_search(root->left, key);
        } else {
            return os_tree_search(root->right, key);
        }
    }
    return NULL;
}

size_t os_tree_find_counts_less_than(os_tree_s *root, int64_t num) {
    if (root != NULL && root != T) {
        //printf("root->left->key: %ld", root->left->key);
        if (root->key < num) {
            return root->size;
        } else if (root->left->key < num) {
            return root->left->size;
        }
        return os_tree_find_counts_less_than(root->left, num);
    }
    return 0;
}

os_tree_s *os_tree_maximum(os_tree_s *root) {
    if (root != NULL) {
        while (root->right != T) {
            root = root->right;
        }
        return root;
    }
    return NULL;
}

os_tree_s *os_tree_minimum(os_tree_s *root) {
    if (root != NULL) {
        while (root->left != T) {
            root = root->left;
        }
        return root;
    }
    return NULL;
}

os_tree_s *os_tree_predecessor(os_tree_s *x) {
    if (x->left != T) {
        return os_tree_minimum(x->left);
    }
    os_tree_s *y = x->p;
    while (y != T && x == y->left) {
        x = y;
        y = y->p;
    }
    return y;
}

os_tree_s *os_tree_successor(os_tree_s *x) {
    if (x->right != T) {
        return os_tree_minimum(x->right);
    }
    os_tree_s *y = x->p;
    while (y != T && x == y->right) {
        x = y;
        y = y->p;
    }
    return y;
}

static bool os_tree_right_rotate(os_tree_s **root, os_tree_s *x) {
    if (root != NULL && x != NULL) {
        if (*root == NULL) {
            return false;
        }
        os_tree_s *y = x->left;
        x->left = y->right;

        if (y->right != T) {
            y->right->p = x;
        }
        y->p = x->p;

        if (x->p == T) {
            *root = y;
        } else if (x == x->p->right) {
            x->p->right = y;
        } else {
            x->p->left = y;
        }

        y->right = x;
        x->p = y;
        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
        return true;
    }
    return false;
}

static bool os_tree_left_rotate(os_tree_s **root, os_tree_s *x) {
    if (root != NULL && x != NULL) {
        if (*root == NULL) {
            return false;
        }
        os_tree_s *y = x->right;
        x->right = y->left;

        if (y->left != T) {
            y->left->p = x;
        }
        y->p = x->p;

        if (x->p == T) {
            *root = y;
        } else if (x == x->p->left) {
            x->p->left = y;
        } else {
            x->p->right = y;
        }

        y->left = x;
        x->p = y;
        y->size = x->size;
        x->size = x->left->size + x->right->size + 1;
        return true;
    }
    return false;
}

static bool os_tree_insert_fixup(os_tree_s **root, os_tree_s *z) {
    os_tree_s *y;
    if (root != NULL && z != NULL) {
        while (z->p->color == RED) {
            if (z->p == z->p->p->left) {
                y = z->p->p->right;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->right) {
                        z = z->p;
                        os_tree_left_rotate(root, z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    os_tree_right_rotate(root, z->p->p);
                }
            } else {
                y = z->p->p->left;
                if (y->color == RED) {
                    z->p->color = BLACK;
                    y->color = BLACK;
                    z->p->p->color = RED;
                    z = z->p->p;
                } else {
                    if (z == z->p->left) {
                        z = z->p;
                        os_tree_right_rotate(root, z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    os_tree_left_rotate(root, z->p->p);
                }
            }
        }
        (*root)->color = BLACK;
        return true;
    }
    return false;
}

bool os_tree_insert(os_tree_s **root, int64_t object) {
    if (root != NULL) {
        if (*root == NULL) {
            return false;
        }
        os_tree_s *z = new_os_tree_node(object);
        z->size = 1;
        if (z == NULL) {
            return false;
        }
        os_tree_s *x = *root;
        os_tree_s *y = T;
        while (x != T) {
            x->size++;
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->p = y;
        if (y == T) {
            *root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = T;
        z->right = T;
        z->color = RED;
        return os_tree_insert_fixup(root, z);
    }
    return false;
}

static bool os_tree_transplant(os_tree_s **root, os_tree_s *u, os_tree_s *v) {
    if (root != NULL && v != NULL && u != NULL) {
        if (*root != NULL) {
            if (u->p == T) {
                (*root) = v;
            } else if (u == u->p->left) {
                u->p->left = v;
            } else {
                u->p->right = v;
            }
            v->p = u->p;
            return true;
        }
        return false;
    }
    return false;
}

static bool os_tree_delete_fix(os_tree_s **root, os_tree_s *x) {
    if (root != NULL && x != NULL) {
        if (*root != NULL) {
            os_tree_s *w;
            while ((x != *root) && (x->color == BLACK)) {
                if (x == x->p->left) {
                    w = x->p->right;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->p->color - RED;
                        os_tree_left_rotate(root, x->p);
                        w = x->p->right;
                    }
                    if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                        w->color = RED;
                        x = x->p;
                    } else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            os_tree_right_rotate(root, w);
                            w = x->p->right;
                        }
                        w->color = x->p->color;
                        x->p->color = BLACK;
                        x->right->color = BLACK;
                        os_tree_left_rotate(root, x->p);
                        x = *root;
                    }
                } else {
                    w = x->p->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->p->color = RED;
                        os_tree_right_rotate(root, x->p);
                        w = x->p->left;
                    }
                    if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
                        w->color = RED;
                        x = x->p;
                    } else {
                        if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            os_tree_left_rotate(root, w);
                            w = x->p->left;
                        }
                        w->color = x->p->color;
                        x->p->color = BLACK;
                        w->left->color = BLACK;
                        os_tree_right_rotate(root, x->p);
                        x = *root;
                    }
                }
            }
            x->color = BLACK;
            return true;
        }
        return false;
    }
    return false;
}

bool os_tree_delete(os_tree_s **root, int64_t key) {
    os_tree_s *z = os_tree_search(*root, key);
    if (root != NULL && z != NULL) {
        if (*root != NULL) {
            os_tree_s *x;
            os_tree_s *y = z;
            enum tree_color y_original_color = y->color;
            if (z->left == T) {
                x = z->right;
                os_tree_transplant(root, z, z->right);
            } else if (z->right == T) {
                x = z->left;
                os_tree_transplant(root, z, z->left);
            } else {
                y = (*root)->left;
                while ((*root)->left != T) {
                    y->size--;
                    y = (*root)->left;
                }
                y_original_color = y->color;
                x = y->right;
                if (y != z->right) {
                    os_tree_transplant(root, y, y->right);
                    y->right = z->right;
                    y->right->p = y;
                } else {
                    x->p = y;
                }
                os_tree_transplant(root, z, y);
                y->left = z->left;
                y->left->p = y;
                y->color = z->color;
            }
            if (y_original_color == BLACK) {
                os_tree_delete_fix(root, x);
            }
        }
        return true;
    }
    return false;
}

os_tree_s *os_tree_select(os_tree_s *x, size_t i) {
    if (x != NULL && i > 0) {
        size_t r = x->left->size + 1;
        if (i == r) {
            return x;
        } else if (i < r) {
            return os_tree_select(x->left, i);
        } else {
            return os_tree_select(x->right, i - r);
        }
    }
    return NULL;
}

size_t os_tree_rank(os_tree_s *root, os_tree_s *x) {
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


void os_tree_print(os_tree_s *root, int depth) {
    if (root != T && root != NULL) {
        os_tree_print(root->right, depth + 1);
        if (depth == 0) {
            printf("----%ld\n", root->key);
        } else if (root->p->right == root) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("/---%ld\n", root->key);
        } else if (root->p->left == root) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("\\---%ld\n", root->key);
        }
        os_tree_print(root->left, depth + 1);

    } else {
        return;
    }
}

void os_tree_print_to(FILE *stream, os_tree_s *root, int depth) {
    if (root != T && root != NULL) {
        os_tree_print_to(stream, root->right, depth + 1);
        if (depth == 0) {
            printf("----%ld\n", root->key);
        } else if (root->p->right == root) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("/---%ld\n", root->key);
        } else if (root->p->left == root) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("\\---%ld\n", root->key);
        }
        os_tree_print_to(stream, root->left, depth + 1);
    } else {
        return;
    }
}

void os_tree_destroy(os_tree_s *x) {
    if (x != NULL && x != T) {
        os_tree_destroy(x->right);
        os_tree_destroy(x->left);
        free(x);
    }
}