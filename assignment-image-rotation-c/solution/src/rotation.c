#include "../include/rotation.h"

int rotate(char* source_filename, char* rotated_filename) {
    /* opening source file in reading mode */
    FILE* file;
    enum file_status file_status = file_open(&file, source_filename, "r");

    /* checking source file opening status */
    if (file_status != FILE_SUCCESS) {
        file_print_status(file_status, source_filename);
        return -1;
    }

    /* creating an internal representation of source image, stripped of format details */
    struct image source_image;
    enum bmp_status bmp_status = from_bmp(file, &source_image);

    /* closing source BMP file */
    file_status = file_close(&file);

    /* checking source file closing status */
    if (file_status != FILE_SUCCESS) {
        image_destroy(&source_image);
        file_print_status(file_status, source_filename);
        return -1;
    }

    /* checking converting source_bmp->struct_source_image status */
    if (bmp_status != BMP_SUCCESS) {
        image_destroy(&source_image);
        bmp_print_status(bmp_status, source_filename);
        return -1;
    }

    /* image rotation */
    struct image rotated_image;
    image_rotate(&source_image, &rotated_image);

    /* creating (if the file does not exist) or erasing the file (if the file already exists) to store the result
     * and opening this file */
    file_status = file_open(&file, rotated_filename, "w");

    /* checking result file opening status */
    if (file_status != FILE_SUCCESS) {
        image_destroy(&source_image);
        image_destroy(&rotated_image);
        file_print_status(file_status, source_filename);
        return -1;
    }

    /* writing an internal representation of rotated image to result BMP file */
    bmp_status = to_bmp(file, &rotated_image);

    /* closing result BMP file */
    file_status = file_close(&file);

    /* checking result file closing status */
    if (file_status != FILE_SUCCESS) {
        image_destroy(&source_image);
        image_destroy(&rotated_image);
        file_print_status(file_status, source_filename);
        return -1;
    }

    /* checking converting struct_rotated_image->result_bmp status */
    if (bmp_status != BMP_SUCCESS) {
        image_destroy(&source_image);
        image_destroy(&rotated_image);
        bmp_print_status(bmp_status, source_filename);
        return -1;
    }

    /* memory clearing */
    image_destroy(&source_image);
    image_destroy(&rotated_image);

    return 0;
}
