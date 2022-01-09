//
// Created by Ньургун Макаров on 05.01.2022.
//
#include "../../include/bmp/bmp_reader_writer.h"
#include <inttypes.h>

enum read_status read_header(FILE *file, struct bmp_header *header) {
    if (fread(header, sizeof(struct bmp_header), 1, file) == 1)
        return READ_CONTINUE;
    return READ_INVALID_HEADER;
}

enum read_status read_pixels(FILE *file, struct image *image, struct bmp_header header) {
    const uint64_t width = header.biWidth;
    const uint64_t height = header.biHeight;
    const uint64_t offset = get_padding(width);
    *image = create_image(width, height);
    struct pixel *const pixels = image->data;
    for (uint32_t i = 0; i < height; i++) {
        if (fread(pixels + width * i, sizeof(struct pixel), width, file) != width ||
            fseek(file, offset, SEEK_CUR) != 0)
            return READ_INVALID_BITS;
    }
    return READ_CONTINUE;

}

enum write_status write_pixels(FILE *file, struct image const *image) {
    const uint32_t width = image->width;
    const uint32_t height = image->height;
    uint8_t offset = get_padding(width);
    struct pixel *pixels = image->data;
    const uint8_t *const offsets[3] = {0};
    for (size_t i = 0; i < height; i++) {
        if (!fwrite(pixels + i * width, sizeof(struct pixel) * width, 1, file)) return WRITE_ERROR;
        if (!fwrite(offsets, offset, 1, file)) return WRITE_ERROR;
    }
    return WRITE_OK;
}


uint64_t get_padding(const uint64_t width) {
    return width % 4 == 0 ? 0 : 4 - ((width * sizeof(struct pixel)) % 4);
}
