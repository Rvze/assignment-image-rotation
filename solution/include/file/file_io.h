//
// Created by Ньургун Макаров on 04.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_FILE_IO_H
#define ASSIGNMENT_IMAGE_ROTATION_FILE_IO_H

#include <stdbool.h>
#include <stdio.h>

enum io_return_code {
    OPEN_OK = 0,
    CLOSE_OK,
    OPEN_ERROR,
    CLOSE_ERROR,
    FILE_IS_CLOSED_ERROR,
    INCORRECT_FILE_NAME
};

extern const char *io_return_code_string[];


enum io_return_code open_file(FILE **file, const char *file_name, const char *mode);

enum io_return_code close_file(FILE *const *file);

static inline enum io_return_code open_file_in_mode(const char *file_name, FILE **file, const char *mode);

#endif //ASSIGNMENT_IMAGE_ROTATION_FILE_IO_H
