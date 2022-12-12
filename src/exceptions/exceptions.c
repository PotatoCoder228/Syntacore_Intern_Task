//
// Created by potato_coder on 04.12.22.
//

#include "../../include/exceptions.h"
#include <bits/types/FILE.h>
#include <stdio.h>

void app_print_status(FILE* file, int status){
    switch (status) {
        case FILE_READ_ERROR:
            fprintf(file,"\n[Ошибка при чтении из потока. Код статуса: ");
            fprintf(file, "%d", FILE_READ_ERROR);
            fprintf(file, "]\n");
            break;
        default:
            fprintf(file,"\n[Непредвиденный статус ошибки. Код статуса: ");
            fprintf(file, "%d", status);
            fprintf(file, "]\n");
            break;
    }

}
