//
// Created by potato_coder on 04.12.22.
//

#include "../../include/exceptions.h"
#include <stdio.h>

void app_print_status(FILE *file, int status) {
    switch (status) {
        case FILE_READ_ERROR:
            fprintf(file, "%s%d%s", "\n[Ошибка при чтении из потока. Код статуса: ", FILE_READ_ERROR, "]\n");
            break;
        default:
            fprintf(file, "%s%d%s", "\n[Непредвиденный статус ошибки. Код статуса: ", status, "]\n");
    }

}
