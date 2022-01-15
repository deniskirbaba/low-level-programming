#ifndef FILE_H
#define FILE_H

#include <stdio.h>

enum file_status {
    FILE_NOT_EXIST = 0,
    FILE_PERMISSION_DENIED,
    FILE_OPEN_ERROR,
    FILE_CLOSE_ERROR,
    FILE_SUCCESS
};

void file_print_status(enum file_status status, char* filename);

enum file_status file_open(FILE** file, const char* filename, const char* mode);
enum file_status file_close(FILE** file);

#endif
