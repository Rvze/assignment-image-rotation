//
// Created by Ньургун Макаров on 05.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_BMP_READER_WRITER_H
#define ASSIGNMENT_IMAGE_ROTATION_BMP_READER_WRITER_H

#include "bmp.h"
#include "../image_manager/image_manager.h"

enum read_status read_header(FILE *file, struct bmp_header *header);

enum read_status read_pixels(FILE *file, struct image *image, struct bmp_header header);

enum write_status write_pixels(FILE *file, const struct image *image);

uint64_t get_padding(uint64_t width);

#endif //ASSIGNMENT_IMAGE_ROTATION_BMP_READER_WRITER_H
