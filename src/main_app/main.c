#include <stdint.h>
#include "../../include/app.h"
#include "../tests/tests.h"
#include "../../include/singly_linked_list.h"

linked_list *commands_help_list;
int8_t is_working;

int main(void) {
    linked_list_test();
    return app_start();
}
