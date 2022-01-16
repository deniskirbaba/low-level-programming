#include "../include/file.h"
#include <errno.h>

enum file_status file_open(FILE** file, char* const filename, char* const mode) {
    *file = fopen(filename, mode);

    if (*file != NULL) return FILE_SUCCESS;
    if (errno == ENOENT) return FILE_NOT_EXIST;
    if (errno == EACCES) return FILE_PERMISSION_DENIED;

    return FILE_OPEN_ERROR;
}

enum file_status file_close(FILE** file){
    if (*file) {
        if (fclose(*file)) {
            return FILE_CLOSE_ERROR;
        }
        return FILE_SUCCESS;
    }
    return FILE_NOT_EXIST;
}

void file_print_status(enum file_status status, char* const filename) {
    switch (status) {
        case FILE_NOT_EXIST:
            fprintf(stderr, "File <%s> doesn't exists", filename);
            break;
        case FILE_PERMISSION_DENIED:
            fprintf(stderr, "Not enough permissions to work with the file <%s>", filename);
            break;
        case FILE_OPEN_ERROR:
            fprintf(stderr, "An error occurred while opening the file <%s>", filename);
            break;
        case FILE_CLOSE_ERROR:
            fprintf(stderr, "An error occurred while closing the file <%s>", filename);
            break;
        case FILE_SUCCESS:
            break;
    }
}
