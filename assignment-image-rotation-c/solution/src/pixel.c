#include "../include/pixel.h"

struct pixel* pixel_alloc_array(size_t size) {
    return malloc(size * sizeof(struct pixel));
}
