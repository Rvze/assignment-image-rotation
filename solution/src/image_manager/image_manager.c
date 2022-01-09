//
// Created by Ньургун Макаров on 04.01.2022.
//

#include "../../include/image_manager/image_manager.h"
#include <mm_malloc.h>

struct image create_image(size_t width, size_t height) {
    struct image newImage = {0};
    newImage.width = width;
    newImage.height = height;
    newImage.data = malloc(width * height * sizeof(struct pixel));
    return newImage;

}

void delete_image(struct image *image) {
    if (image) {
        if (image->data)
            free(image->data);
    }
}

struct pixel get_pixel(const struct image *image, const size_t row, const size_t column) {
    return image->data[row * image->width + column];
}

bool set_pixel(struct image *image, const struct pixel pixel, const size_t row, const size_t column) {
    size_t pos = row * image->width + column;
    if (!is_valid_pos(*image, pos)) {
        return false;
    }
    image->data[pos] = pixel;
    return true;
}

size_t get_image_size(const struct image *image) {
    return image->width * image->width * sizeof(struct pixel);
}

bool is_valid_pos(struct image image, size_t pos) {
    return pos < image.width * image.height;
}

struct image some_image(uint64_t width, uint64_t height, struct pixel *data) {
    return (struct image) {.width = width, .height = height, .data = data};
}
