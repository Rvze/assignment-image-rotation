//
// Created by Ньургун Макаров on 05.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_READER_WRITER_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_READER_WRITER_H

#include "../image_manager/image_manager.h"
#include "bmp.h"


enum read_status read_pixels(FILE *file, struct image *image);

enum write_status write_pixels(FILE *file, const struct image *image);

uint8_t get_padding(uint32_t width);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_READER_WRITER_H
