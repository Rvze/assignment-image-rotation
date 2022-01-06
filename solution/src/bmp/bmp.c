//
// Created by Ньургун Макаров on 05.01.2022.
//
//#include "../../include/bmp/bmp.h"
#include <mm_malloc.h>
#include "../../include/bmp/bmp_reader.h"

static uint32_t TYPE = 19778;
static uint32_t RESERVED = 0;
static uint32_t HEADER_SIZE = 40;
static uint16_t PLANES = 1;
static uint32_t COMPRESSION = 0;
static uint32_t PIXEL_PER_M = 2834;
static uint32_t COLORS_USED = 0;
static uint32_t COLORS_IMPORTANT = 0;
static size_t BIT_COUNT = 24;

const char *read_status_string[] = {
        [READ_OK] = "Read ok",
        [READ_INVALID_SIGNATURE] = "Invalid signature",
        [READ_INVALID_BITS] = "Invalid bits",
        [READ_INVALID_HEADER] = "Invalid header",
        [READ_NULL] = "Read null"
};

const char *write_status_string[] = {
        [WRITE_OK] = "Write ok\n",
        [WRITE_ERROR] = "Write error\n"
};

static struct bmp_header make_header(const struct image *image) {
    struct bmp_header new_header = {
            .bfType = TYPE,
            .bfReserved = RESERVED,
            .bOffBits = sizeof(struct bmp_header),
            .biSize = HEADER_SIZE,
            .biPlanes = PLANES,
            .biCompression = COMPRESSION,
            .biXPelsPerMeter = PIXEL_PER_M,
            .biYPelsPerMeter = PIXEL_PER_M,
            .biClrUsed = COLORS_USED,
            .biClrImportant = COLORS_IMPORTANT,
            .biBitCount = BIT_COUNT
    };
    size_t image_size = get_image_size(image);
    new_header.biSizeImage = image_size;
    new_header.biWidth = image->width;
    new_header.biHeight = image->height;
    new_header.bfileSize = sizeof(struct bmp_header) + image_size;
    return new_header;
}

enum read_status from_bmp(FILE *file, struct image *image) {
    if (!file || !image)
        return READ_NULL;
    struct bmp_header header;
    enum read_status status = read_header(file, &header);
    if (status != READ_CONTINUE)
        return status;
    image->width = header.biWidth;
    image->height = header.biHeight;
    image = create_image(image->width, image->height);
    status = read_pixels(file, image);
    if (status != READ_CONTINUE)
        return status;
    return READ_OK;
}

enum write_status to_bmp(FILE *file, struct image const *image) {
    struct bmp_header header = make_header(image);
    if (!fwrite(&header, sizeof(struct bmp_header), 1, file))
        return WRITE_ERROR;
    fseek(file, header.bOffBits, SEEK_SET);
    const int8_t zero = 0;
    const size_t padding = get_padding(image->width);
    if (image->data != NULL) {
        for (size_t i = 0; i < image->height; ++i) {
            fwrite(image->data + i * image->width, image->width * sizeof(struct pixel), 1, file);
            for (size_t j = 0; j < padding; ++j) {
                fwrite(&zero, 1, 1, file);
            }
        }
    } else {
        return WRITE_ERROR;
    }
    return WRITE_OK;
}
