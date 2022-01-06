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
    const uint8_t zero_line = 0;
    if (image->data == NULL)
        return WRITE_ERROR;
    for (size_t i = 0; i < image->height; i++) {
        void *const start = image->data + i * image->width;
        size_t const size = image->width * sizeof(struct pixel);
        fwrite(start, size, 1, file);
        for (size_t j = 0; j < get_padding(*image); j++) {
            fwrite(&zero_line, 1, 1, file);
        }
    }
    return WRITE_OK;

}