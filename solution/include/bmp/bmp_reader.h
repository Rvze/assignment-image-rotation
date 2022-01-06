//
// Created by Ньургун Макаров on 05.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_READER_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_READER_H

#include "bmp.h"
#include "../image_manager/image_manager.h"

enum read_status read_header(FILE *file, struct bmp_header *header);

enum read_status read_pixels(FILE *file, struct image *image);

size_t get_padding(struct image image);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_READER_H
