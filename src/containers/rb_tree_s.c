//
// Created by sasha on 04.03.2023.
//

#include "../../include/containers/rb_tree_s.h"


/**
 * Обобщённая версия красно-чёрного дерева(на основе которого построено расширенное, но с int64_t)
 * */

typedef struct rb_tree_s {
    enum tree_color color;
    rb_tree_s *p;
    rb_tree_s *left;
    rb_tree_s *right;
    object_s *key;
} rb_tree_s;

void rb_tree_set_color(rb_tree_s *node, enum tree_color color) {
    if (node != NULL) {
        node->color = color;
    }
}

void rb_tree_set_key(rb_tree_s *node, object_s *key) {
    if (node != NULL) {
        node->key = key;
    }
}

void rb_tree_set_parent(rb_tree_s *node, rb_tree_s *parent) {
    if (node != NULL) {
        node->p = parent;
    }
}

void rb_tree_set_left(rb_tree_s *node, rb_tree_s *left) {
    if (node != NULL) {
        node->left = left;
    }
}

void rb_tree_set_right(rb_tree_s *node, rb_tree_s *right) {
    if (node != NULL) {
        node->right = right;
    }
}

object_s *rb_tree_get_key(rb_tree_s *node) {
    if (node != NULL) {
        return node->key;
    }
    return NULL;
}

enum tree_color rb_tree_get_color(rb_tree_s *node) {
    if (node != NULL) {
        return node->color;
    }
    return BLACK;
}

rb_tree_s *rb_tree_get_parent(rb_tree_s *node) {
    if (node != NULL) {
        return node->p;
    }
    return NULL;
}

rb_tree_s *rb_tree_get_left(rb_tree_s *node) {
    if (node != NULL) {
        return node->left;
    }
    return NULL;
}

rb_tree_s *rb_tree_get_right(rb_tree_s *node) {
    if (node != NULL) {
        return node->right;
    }
    return NULL;
}

static rb_tree_s nil = {.p = NULL, .left = NULL, .right = NULL, .key = NULL, .color = BLACK};
static rb_tree_s *T = &nil;

rb_tree_s *new_rb_tree(object_s *key) {
    nil.p = T;
    nil.left = T;
    nil.right = T;
    rb_tree_s *new_tree = malloc(sizeof(rb_tree_s));
    if (new_tree) {
        new_tree->color = BLACK;
        new_tree->p = T;
        new_tree->left = T;
        new_tree->right = T;
        new_tree->key = key;
    }
    return new_tree;
}

static rb_tree_s *new_rb_tree_node(object_s *key) {
    rb_tree_s *new_tree = malloc(sizeof(rb_tree_s));
    if (new_tree) {
        new_tree->color = BLACK;
        new_tree->p = T;
        new_tree->left = T;
        new_tree->right = T;
        new_tree->key = key;
    }
    return new_tree;
}

rb_tree_s *rb_tree_search(rb_tree_s *node, object_s *key, int compare(void *, void *)) {
    if (node != NULL) {
        if (node == T || object_compare(key, node->key, compare) == 0) {
            return node;
        }
        if (object_compare(key, node->key, compare) == -1) {
            return rb_tree_search(node->left, key, compare);
        } else {
            return rb_tree_search(node->right, key, compare);
        }
    }
    return NULL;
}

rb_tree_s *rb_tree_maximum(rb_tree_s *root) {
    if (root != NULL) {
        while (root->right != T) {
            root = root->right;
        }
        return root;
    }
    return NULL;
}

rb_tree_s *rb_tree_minimum(rb_tree_s *root) {
    if (root != NULL) {
        while (root->left != T) {
            root = root->left;
        }
        return root;
    }
    return NULL;
}

rb_tree_s *rb_tree_predecessor(rb_tree_s *node) {
    if (node->left != T) {
        return rb_tree_minimum(node->left);
    }
    rb_tree_s *y = node->p;
    while (y != T && node == y->left) {
        node = y;
        y = y->p;
    }
    return y;
}

rb_tree_s *rb_tree_successor(rb_tree_s *node) {
    if (node->right != T) {
        return rb_tree_minimum(node->right);
    }
    rb_tree_s *y = node->p;
    while (y != T && node == y->right) {
        node = y;
        y = y->p;
    }
    return y;
}

static bool rb_tree_right_rotate(rb_tree_s **root, rb_tree_s *x) {
    if (root != NULL && x != NULL) {
        if (*root == NULL) {
            return false;
        }
        rb_tree_s *y = x->left;
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
        return true;
    }
    return false;
}

static bool rb_tree_left_rotate(rb_tree_s **root, rb_tree_s *x) {
    if (root != NULL && x != NULL) {
        if (*root == NULL) {
            return false;
        }
        rb_tree_s *y = x->right;
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
        return true;
    }
    return false;
}

static bool rb_tree_insert_fix(rb_tree_s **root, rb_tree_s *z) {
    rb_tree_s *y;
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
                        rb_tree_left_rotate(root, z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    rb_tree_right_rotate(root, z->p->p);
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
                        rb_tree_right_rotate(root, z);
                    }
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    rb_tree_left_rotate(root, z->p->p);
                }
            }
        }
        (*root)->color = BLACK;
        return true;
    }
    return false;
}

bool rb_tree_insert(rb_tree_s **root, object_s *key, int compare(void *, void *)) {
    if (root != NULL) {
        if (*root == NULL) {
            return false;
        }
        rb_tree_s *z = new_rb_tree_node(key);
        if (z == NULL) {
            return false;
        }
        rb_tree_s *x = *root;
        rb_tree_s *y = T;
        while (x != T) {
            y = x;
            if (object_compare(z->key, x->key, compare) == -1) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->p = y;
        if (y == T) {
            *root = z;
        } else if (object_compare(z->key, y->key, compare) == -1) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = T;
        z->right = T;
        z->color = RED;
        return rb_tree_insert_fix(root, z);
    }
    return false;
}

static bool rb_tree_transplant(rb_tree_s **root, rb_tree_s *from, rb_tree_s *to) {
    if (root != NULL && to != NULL && from != NULL) {
        if (*root != NULL) {
            if (from->p == T) {
                (*root) = to;
            } else if (from == from->p->left) {
                from->p->left = to;
            } else {
                from->p->right = to;
            }
            to->p = from->p;
            return true;
        }
        return false;
    }
    return false;
}

static bool rb_tree_delete_fix(rb_tree_s **root, rb_tree_s *x) {
    if (root != NULL && x != NULL) {
        if (*root != NULL) {
            rb_tree_s *w;
            while ((x != *root) && (x->color == BLACK)) {
                if (x == x->p->left) {
                    w = x->p->right;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->p->color - RED;
                        rb_tree_left_rotate(root, x->p);
                        w = x->p->right;
                    }
                    if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                        w->color = RED;
                        x = x->p;
                    } else {
                        if (w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            rb_tree_right_rotate(root, w);
                            w = x->p->right;
                        }
                        w->color = x->p->color;
                        x->p->color = BLACK;
                        x->right->color = BLACK;
                        rb_tree_left_rotate(root, x->p);
                        x = *root;
                    }
                } else {
                    w = x->p->left;
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->p->color = RED;
                        rb_tree_right_rotate(root, x->p);
                        w = x->p->left;
                    }
                    if ((w->right->color == BLACK) && (w->left->color == BLACK)) {
                        w->color = RED;
                        x = x->p;
                    } else {
                        if (w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            rb_tree_left_rotate(root, w);
                            w = x->p->left;
                        }
                        w->color = x->p->color;
                        x->p->color = BLACK;
                        w->left->color = BLACK;
                        rb_tree_right_rotate(root, x->p);
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

bool rb_tree_delete(rb_tree_s **root, object_s *key, int compare(void *, void *)) {
    rb_tree_s *z = rb_tree_search(*root, key, compare);
    if (root != NULL && z != NULL) {
        if (*root != NULL) {
            rb_tree_s *x;
            rb_tree_s *y = z;
            enum tree_color y_original_color = y->color;
            if (z->left == T) {
                x = z->right;
                rb_tree_transplant(root, z, z->right);
            } else if (z->right == T) {
                x = z->left;
                rb_tree_transplant(root, z, z->left);
            } else {
                y = rb_tree_minimum(*root);
                y_original_color = y->color;
                x = y->right;
                if (y != z->right) {
                    rb_tree_transplant(root, y, y->right);
                    y->right = z->right;
                    y->right->p = y;
                } else {
                    x->p = y;
                }
                rb_tree_transplant(root, z, y);
                y->left = z->left;
                y->left->p = y;
                y->color = z->color;
            }
            if (y_original_color == BLACK) {
                rb_tree_delete_fix(root, x);
            }
        }
        return true;
    }
    return false;
}

void rb_tree_print(rb_tree_s *node, char *(to_string)(void *), int depth) {
    if (node != T && node != NULL) {
        rb_tree_print(node->right, to_string, depth + 1);
        if (depth == 0) {
            printf("----%s\n", object_to_string(node->key, to_string));
        } else if (node->p->right == node) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("/---%s\n", object_to_string(node->key, to_string));
        } else if (node->p->left == node) {
            for (int i = 0; i < depth; i++) {
                printf("     ");
            }
            printf("\\---%s\n", object_to_string(node->key, to_string));
        }
        rb_tree_print(node->left, to_string, depth + 1);
    } else {
        return;
    }
}

void rb_tree_print_to(FILE *stream, rb_tree_s *node, char *(to_string)(void *), int depth) {
    if (node != T && node != NULL) {
        rb_tree_print_to(stream, node->right, to_string, depth + 1);
        if (depth == 0) {
            fprintf(stream, "----%s\n", object_to_string(node->key, to_string));
        } else if (node->p->right == node) {
            for (int i = 0; i < depth; i++) {
                fprintf(stream, "     ");
            }
            fprintf(stream, "/---%s\n", object_to_string(node->key, to_string));
        } else if (node->p->left == node) {
            for (int i = 0; i < depth; i++) {
                fprintf(stream, "     ");
            }
            fprintf(stream, "\\---%s\n", object_to_string(node->key, to_string));
        }
        rb_tree_print_to(stream, node->left, to_string, depth + 1);
    } else {
        return;
    }
}


void rb_tree_destroy(rb_tree_s *node, void (*destroyer)(void *)) {
    if (node != NULL && node != T) {
        rb_tree_destroy(node->right, destroyer);
        rb_tree_destroy(node->left, destroyer);
        object_destroy(node->key, destroyer);
        free(node);
    }
}