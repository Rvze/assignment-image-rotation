//
// Created by Ньургун Макаров on 05.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_MANAGER_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_MANAGER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t width, height;
    struct pixel *data;
};

struct image create_image(size_t width, size_t height);

void delete_image(struct image *image);


struct pixel get_pixel(const struct image *image, size_t row, size_t column);

bool set_pixel(struct image *image, struct pixel pixel, const size_t row, const size_t column);

size_t get_image_size(const struct image *image);

bool is_valid_pos(struct image image, size_t pos);

struct image some_image(uint32_t width, uint32_t height, struct pixel *data);


#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_MANAGER_H
