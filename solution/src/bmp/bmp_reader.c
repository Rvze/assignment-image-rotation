//
// Created by Ньургун Макаров on 05.01.2022.
//
#include "../../include/bmp/bmp_reader.h"

enum read_status read_header(FILE *file, struct bmp_header *header) {
    if (fseek(file, 0, SEEK_END) != 0) {
        return READ_INVALID_HEADER;
    }
    if (ftell(file) < sizeof(struct bmp_header)) {
        return READ_INVALID_HEADER;
    }
    fseek(file, 0, SEEK_SET);

    if (fread(header, sizeof(struct bmp_header), 1, file) == 1) {
        return READ_OK;
    } else
        return READ_INVALID_HEADER;
}

enum read_status read_pixels(FILE *file, struct image *image) {
    size_t padding = get_padding(*image);
    for (size_t i = 0; i < image->height; i++) {
        size_t file_read = fread(image->data + i * image->width, image->width * sizeof(struct pixel), 1, file);
        if (file_read != 1)
            return READ_NULL;
        if (fseek(file, padding, SEEK_CUR) != 0)
            return READ_NULL;
    }
    return READ_OK;
}

size_t get_padding(struct image image) {
    if ((4 - image.width * 3 % 4) == 0)
        return 0;
    return 4 - image.width * 3 % 4;
}