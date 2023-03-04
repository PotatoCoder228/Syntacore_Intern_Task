//
// Created by sasha on 04.03.2023.
//

#include <stdlib.h>
#include "../include/app.h"

int main() {
    error_s *error = new_error();
    app_start(error);
    error_destroy(error);
    return EXIT_SUCCESS;
}