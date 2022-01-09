//
// Created by Ньургун Макаров on 05.01.2022.
//
//#include "../../include/bmp/bmp.h"
#include <mm_malloc.h>
#include "../../include/bmp/bmp_reader_writer.h"

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
        [READ_NULL] = "Read null",
        [READ_CONTINUE] = "Read continue"
};

const char *write_status_string[] = {
        [WRITE_OK] = "Write ok\n",
        [WRITE_ERROR] = "Write error\n"
};

static enum write_status make_header(FILE *const out, const size_t width, const size_t height) {
    uint8_t padding = get_padding(width);
    const size_t image_size = (sizeof(struct pixel) * (width) + padding) * (height);
    const struct bmp_header new_header = {
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
            .biBitCount = BIT_COUNT,
            .biSizeImage = image_size,
            .biWidth = width,
            .biHeight = height,
            .bfileSize = sizeof(struct bmp_header) + image_size
    };
    if (fwrite(&new_header, sizeof(struct bmp_header), 1, out) != 1) {
        return WRITE_ERROR;
    }
    return WRITE_CONTINUE;
}

enum read_status from_bmp(FILE *file, struct image *image) {
    struct bmp_header header = {0};

    *image = create_image(header.biWidth, header.biHeight);

    const size_t padding = get_padding(image->width);

    for (size_t i = 0; i < image->height; ++i) {
        for (size_t j = 0; j < image->width; ++j) {
            if (fread(&(image->data[image->width * i + j]), sizeof(struct pixel), 1, file) != 1)
                return READ_INVALID_BITS;
        }
        fseek(file, (long) padding, SEEK_CUR);
    }
    return READ_OK;
}


enum write_status to_bmp(FILE *file, const struct image *image) {

    enum write_status status;

    status = make_header(file, image->width, image->height);

    if (status != WRITE_CONTINUE)
        return status;

    status = write_pixels(file, image);

    if (status != WRITE_CONTINUE)
        return status;
    return WRITE_OK;

}


