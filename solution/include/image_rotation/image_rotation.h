//
// Created by Ньургун Макаров on 04.01.2022.
//

#ifndef ASSIGNMENT_IMAGE_ROTATION_IMAGE_ROTATION_H
#define ASSIGNMENT_IMAGE_ROTATION_IMAGE_ROTATION_H

#include <stdbool.h>
#include "../image_manager/image_manager.h"

struct image rotate_image(struct image source);

struct image some_image(uint64_t width, uint64_t height, struct pixel *data);

#endif //ASSIGNMENT_IMAGE_ROTATION_IMAGE_ROTATION_H