#ifndef IMAGE_H
#define IMAGE_H

#include "../include/pixel.h"
#include <stdint.h>

struct image {
    uint64_t width, height;
    struct pixel* data;
};

struct image image_create(uint64_t width, uint64_t height);
void image_destroy(struct image* const image);

uint64_t image_get_width(struct image const* const image);
void image_set_width(struct image* const image, uint64_t width);

uint64_t image_get_height(struct image const* const image);
void image_set_height(struct image* const image, uint64_t height);

struct pixel image_get_pixel(struct image const* const image, uint64_t width, uint64_t height);
void image_set_pixel(struct image* const image, struct pixel pixel, uint64_t width, uint64_t height);

struct pixel* image_get_data(struct image* image);
void image_set_data(struct image* image, struct pixel* data);

void image_rotate(struct image* const source_image, struct image* const rotated_image);

#endif
