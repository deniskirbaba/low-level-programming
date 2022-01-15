#ifndef PIXEL_H
#define PIXEL_H

#include <malloc.h>
#include <stdint.h>
#include <stdio.h>

struct pixel {uint8_t b, g, r;};

struct pixel* pixel_alloc_array(size_t size);

#endif
