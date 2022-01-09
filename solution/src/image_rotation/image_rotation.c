//
// Created by Ньургун Макаров on 04.01.2022.
//

#include "../../include/image_rotation/image_rotation.h"
#include <mm_malloc.h>

struct image rotate_image(const struct image source) {
    if (source.data == NULL)
        return some_image(source.width, source.height, NULL);

    struct pixel *pixels = malloc(sizeof(struct pixel) * source.width * source.height);

    for (size_t i = 0; i < source.height; ++i) {
        for (size_t j = 0; j < source.width; ++j) {
            pixels[source.height * j + (source.height - 1 - i)] = source.data[i * source.width + j];
        }
    }
    return some_image(source.height, source.width, pixels);
}



