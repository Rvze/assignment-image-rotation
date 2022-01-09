//
// Created by Ньургун Макаров on 05.01.2022.
//


#include <stdio.h>
#include "../../include/file/file_io.h"

const char *io_return_code_string[] = {
        [OPEN_OK] = "File is successfully opened",
        [CLOSE_OK] ="File is successfully closed",
        [OPEN_ERROR]="Error when file opening",
        [CLOSE_ERROR] ="Error when file closing",
        [FILE_IS_CLOSED_ERROR]="Error, can't work with closed file",
        [INCORRECT_FILE_NAME]="Error, file name can't be null"
};

enum io_return_code open_file(FILE **file, const char *file_name, const char *mode) {
    if (!file_name)
        return INCORRECT_FILE_NAME;
    *file = fopen(file_name, mode);
    if (!*file)
        return OPEN_ERROR;
    return OPEN_OK;
}

enum io_return_code close_file(FILE *const file) {
    if (file != NULL) {
        fclose(file);
        return CLOSE_OK;
    } else
        return FILE_IS_CLOSED_ERROR;
}

static inline enum io_return_code open_file_in_mode(const char *file_name, FILE **file, const char *mode) {
    if (!file_name)
        return INCORRECT_FILE_NAME;
    *file = fopen(file_name, mode);
    if (!*file)
        return OPEN_ERROR;
    return OPEN_OK;
}
