#include <stdint.h>
#include <malloc.h>
#include "../../include/app.h"
#include "../tests/tests.h"
#include "../../include/singly_linked_list.h"
#include "../../include/rb_tree.h"

linked_list *commands_help_list;
int8_t is_working;

int main(void) {
    //linked_list_test();
    rb_tree* tree = new_rb_tree(64);
    rb_tree* node = new_rb_tree(120);
    rb_tree_insert(&tree, node);
    printf("%ld",rb_tree_get_key(tree));
    //return app_start();
    return 0;
}
