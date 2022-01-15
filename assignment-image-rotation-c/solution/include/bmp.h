#ifndef BMP_H
#define BMP_H

#include "../include/image.h"
#include <stdio.h>

#pragma pack(push, 1)
struct bmp_header
{
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

enum bmp_status  {
    BMP_INVALID_HEADER = 0,
    BMP_ERROR,
    BMP_SUCCESS,
};

void bmp_print_status(enum bmp_status status, char* filename);

enum bmp_status from_bmp(FILE* file, struct image* image);
enum bmp_status to_bmp(FILE* file, struct image* image);

uint8_t get_padding(uint64_t width);
struct bmp_header bmp_create_header(uint64_t width, uint64_t height);

#endif
