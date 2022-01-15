#include "../include/image.h"
#include <malloc.h>

struct image image_create(uint64_t width, uint64_t height) {
    return (struct image) {width, height, malloc(sizeof(struct pixel) * width * height)};
}

void image_destroy(struct image* const image) {
    image->width = 0;
    image->height = 0;
    if (image->data != NULL) free(image->data);
}

uint64_t image_get_height(struct image const* const image) {
    return image->height;
}

void image_set_height(struct image* const image, uint64_t height) {
    image->height = height;
}

uint64_t image_get_width(struct image const* const image) {
    return image->width;
}

void image_set_width(struct image* const image, uint64_t width) {
    image->width = width;
}

struct pixel image_get_pixel(struct image const* const image, uint64_t width, uint64_t height) {
    size_t pixel_index = width + height * image->width;
    return image->data[pixel_index];
}

void image_set_pixel(struct image* const image, struct pixel pixel, uint64_t width, uint64_t height) {
    image->data[height * image->width + width] = pixel;
}

struct pixel* image_get_data(struct image* image) {
    return image->data;
}

void image_set_data(struct image* image, struct pixel* data) {
    image->data = data;
}

void image_rotate(struct image* const source_image, struct image* const rotated_image) {
    /* initialize some useful variables */
    uint64_t rotated_width = image_get_height(source_image);
    uint64_t rotated_height = image_get_width(source_image);

    image_set_width(rotated_image, rotated_width);
    image_set_height(rotated_image, rotated_height);
    struct pixel* pixel_array = pixel_alloc_array(rotated_width * rotated_height);
    image_set_data(rotated_image, pixel_array);

    for (uint64_t i = 0; i < rotated_height; i++) {
        for (uint64_t j = 0; j < rotated_width; j++) {
            struct pixel pixel = image_get_pixel(source_image, i, rotated_width - j - 1);
            image_set_pixel(rotated_image, pixel, j, i);
        }
    }
}
