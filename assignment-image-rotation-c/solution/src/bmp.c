#include "../include/bmp.h"

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

void bmp_print_status(enum bmp_status status, char* filename){
    switch (status) {
        case BMP_INVALID_HEADER:
            fprintf(stderr, "The file <%s> does not match the BMP-format (invalid header)", filename);
            break;
        case BMP_ERROR:
            fprintf(stderr, "The file <%s> does not match the BMP-format", filename);
            break;
        case BMP_SUCCESS:
            break;
    }
}

uint8_t get_padding(uint64_t width){
    if (width % 4 == 0) return 0;
    return 4 - (width * sizeof(struct pixel)) % 4;
}

struct bmp_header bmp_create_header(uint64_t width, uint64_t height) {
    const uint32_t head_size = sizeof(struct bmp_header);
    const uint32_t img_size = sizeof(struct pixel) * height * (width + get_padding(width));
    const uint32_t file_size = head_size + img_size;

    return (struct bmp_header) {
            .bfType = 0x4D42,
            .bfileSize = file_size,
            .bfReserved = 0,
            .bOffBits = head_size,
            .biSize = 40,
            .biWidth = width,
            .biHeight = height,
            .biPlanes = 1,
            .biBitCount = 24,
            .biCompression = 0,
            .biSizeImage = img_size,
            .biXPelsPerMeter = 0,
            .biYPelsPerMeter = 0,
            .biClrUsed = 0,
            .biClrImportant = 0
    };
}

enum bmp_status from_bmp(FILE* file, struct image* const image) {
    /* checking file */
    if(file == NULL) return BMP_ERROR;

    /* reading bmp header */
    struct bmp_header header;
    rewind(file); // setting the file position to the beginning of the file
    size_t read_elem_num = fread(&header, sizeof(struct bmp_header), 1, file);

    /* checking bmp header */
    if (read_elem_num != 1) return BMP_ERROR;

    unsigned char b_byte = header.bfType & 0xFF;
    unsigned char m_byte = (header.bfType >> 8) & 0xFF;
    if (b_byte != 'B' || m_byte != 'M') return BMP_INVALID_HEADER;

    /* initialize some useful variables */
    uint64_t width = header.biWidth;
    uint64_t height = header.biHeight;

    /* creating and validating pixel array */
    struct pixel* pixel_array = pixel_alloc_array(height * width);
    if (pixel_array == NULL) return BMP_ERROR;

    /* getting padding */
    uint8_t padding = get_padding(width);

    /* reading bmp pixel array */
    for (uint64_t i = 0; i < height; i++) {
        size_t res_fread_value = fread(pixel_array + i * width, sizeof(struct pixel) * width, 1 , file);
        int64_t res_fseek_value = fseek(file, padding, SEEK_CUR);
        if (res_fread_value != 1 || res_fseek_value) {
            free(pixel_array);
            return BMP_ERROR;
        }
    }

    /* writing a BMP-file as a structure_image */
    image_set_height(image, height);
    image_set_width(image, width);
    image_set_data(image, pixel_array);

    return BMP_SUCCESS;
}

enum bmp_status to_bmp(FILE* file, struct image* const image) {
    /* initialize some useful variables */
    uint64_t width = image_get_width(image);
    uint64_t height = image_get_height(image);

    /* creating BMP header */
    struct bmp_header header = bmp_create_header(width, height);

    /* writing header to the result file */
    size_t res_fwrite_header_value = fwrite(&header, sizeof(struct bmp_header), 1, file);
    int64_t res_fseek_value = fseek(file, header.bOffBits, SEEK_SET);
    if (res_fwrite_header_value != 1 || res_fseek_value) return BMP_ERROR;

    /* getting padding */
    uint8_t padding = get_padding(width);
    uint8_t* padding_to_bmp;
    if (padding != 0) padding_to_bmp = calloc(1, padding);

    /* writing pixel array + padding to the result file */
    for (uint64_t i = 0; i < height; i++){
        size_t res_fwrite_pixels_value = fwrite(image_get_data(image) + width * i, width * sizeof(struct pixel), 1, file);
        if (res_fwrite_pixels_value != 1) {
            if (padding != 0) free(padding_to_bmp);
            return BMP_ERROR;
        }
        if (padding != 0) {
            size_t res_fwrite_padding_value = fwrite(padding_to_bmp, padding, 1, file);
            if (res_fwrite_padding_value != 1) {
                free(padding_to_bmp);
                return BMP_ERROR;
            }
        }
    }

    if (padding != 0) free(padding_to_bmp);

    return BMP_SUCCESS;
}
