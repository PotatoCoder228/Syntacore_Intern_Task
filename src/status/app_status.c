//
// Created by potato_coder on 04.12.22.
//

#include "../../include/app_status.h"
#include <bits/types/FILE.h>
#include <stdio.h>

void app_print_status(FILE* file, int status){
    switch (status) {
        case READ_OK:
            fprintf(file,"\n[Чтение прошло успешно. Код статуса: ");
            fprintf(file, "%d", READ_OK);
            fprintf(file, "]\n");
            break;
        case WRITE_OK:
            fprintf(file,"\n[Запись прошла успешно. Код статуса: ");
            fprintf(file, "%d", WRITE_OK);
            fprintf(file, "]\n");
            break;
        case READ_ERROR:
            fprintf(file,"\n[Ошибка при чтении из потока. Код статуса: ");
            fprintf(file, "%d", READ_ERROR);
            fprintf(file, "]\n");
            break;
        case WRITE_ERROR:
            fprintf(file,"\n[Ошибка при записи в поток. Код статуса: ");
            fprintf(file, "%d", WRITE_ERROR);
            fprintf(file, "]\n");
            break;
        default:
            fprintf(file,"\n[Непредвиденный статус программы. Код статуса: ");
            fprintf(file, "%d", WRITE_ERROR);
            fprintf(file, "]\n");
            break;
    }

}
