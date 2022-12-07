//
// Created by potato_coder on 04.12.22.
//

#include "../../include/app_status.h"
#include <bits/types/FILE.h>
#include <stdio.h>

void app_print_status(FILE* file, int status){
    switch (status) {
        case FILE_READ_OK:
            fprintf(file,"\n[Чтение прошло успешно. Код статуса: ");
            fprintf(file, "%d", FILE_READ_OK);
            fprintf(file, "]\n");
            break;
        case FILE_WRITE_OK:
            fprintf(file,"\n[Запись прошла успешно. Код статуса: ");
            fprintf(file, "%d", FILE_WRITE_OK);
            fprintf(file, "]\n");
            break;
        case FILE_READ_ERROR:
            fprintf(file,"\n[Ошибка при чтении из потока. Код статуса: ");
            fprintf(file, "%d", FILE_READ_ERROR);
            fprintf(file, "]\n");
            break;
        case FILE_WRITE_ERROR:
            fprintf(file,"\n[Ошибка при записи в поток. Код статуса: ");
            fprintf(file, "%d", FILE_WRITE_ERROR);
            fprintf(file, "]\n");
            break;
        default:
            fprintf(file,"\n[Непредвиденный статус программы. Код статуса: ");
            fprintf(file, "%d", FILE_WRITE_ERROR);
            fprintf(file, "]\n");
            break;
    }

}
