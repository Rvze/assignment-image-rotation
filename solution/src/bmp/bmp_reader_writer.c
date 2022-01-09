//
// Created by Ньургун Макаров on 05.01.2022.
//
#include "../../include/bmp/bmp_reader_writer.h"
#include <inttypes.h>

static enum read_status read_header(FILE *file, struct bmp_header *header) {
    if (fread(header, sizeof(struct bmp_header), 1, file) == 1)
        return READ_CONTINUE;
    return READ_INVALID_HEADER;
}

static enum read_status read_pixels(FILE *file, struct image *image) {
    const uint64_t width = image->width, height = image->height;
    const uint8_t padding = get_padding(width);
    struct pixel *pixels = image->data;

    for (uint64_t i = 0; i < height; ++i) {
        if (fread(pixels + i * width, sizeof(struct pixel), width, file) != width)
            return READ_INVALID_BITS;
        if (fseek(file, padding, SEEK_CUR))
            return READ_INVALID_BITS;
    }
    return READ_CONTINUE;
}

enum write_status write_pixels(FILE *file, struct image const *image) {
    const uint64_t width = image->width, height = image->height;
    const uint8_t padding = get_padding(width);
    struct pixel *pixels = image->data;
    for (uint64_t i = 0; i < height; ++i) {
        if (fwrite(pixels + i * width, sizeof(struct pixel), width, file) != width)
            return WRITE_ERROR;
        for (uint64_t j = 0; j < padding; ++j) {
            char trash = 0;
            if (fwrite(&trash, 1, 1, file) != 1)
                return WRITE_ERROR;
        }
    }
    return WRITE_CONTINUE;
}


uint64_t get_padding(const uint64_t width) {
    return width % 4 == 0 ? 0 : 4 - ((width * sizeof(struct pixel)) % 4);
}
