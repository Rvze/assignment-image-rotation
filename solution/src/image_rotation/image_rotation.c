//
// Created by Ньургун Макаров on 04.01.2022.
//

#include "../../include/image_rotation/image_rotation.h"
#include <stdbool.h>
#include <mm_malloc.h>

struct image rotate_image(struct image const src) {
    struct image rotated_img;
    rotated_img.data = malloc(sizeof(struct pixel) * src.height * src.width);

    for (size_t i = 0; i < src.height; i++) {
        for (size_t j = 0; j < src.width; j++) {
            rotated_img.data[j * src.height + (src.height - 1 - i)] = src.data[i * src.width + j];
        }
    }
    rotated_img.width = src.height;
    rotated_img.height = src.width;
    return rotated_img;

}