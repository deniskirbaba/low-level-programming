#ifndef BMP_H
#define BMP_H

#include "../include/image.h"
#include <stdio.h>

enum bmp_status  {
    BMP_INVALID_HEADER = 0,
    BMP_ERROR,
    BMP_SUCCESS,
};

void bmp_print_status(enum bmp_status status, char* filename);

enum bmp_status from_bmp(FILE* file, struct image* const image);
enum bmp_status to_bmp(FILE* file, struct image* const image);

#endif
