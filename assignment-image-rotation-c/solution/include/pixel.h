#ifndef PIXEL_H
#define PIXEL_H

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>

struct __attribute__((packed)) pixel {
    uint8_t blue, green, red;
};

struct pixel* pixel_alloc_array(size_t size);

#endif
