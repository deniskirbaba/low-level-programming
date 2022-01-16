#include "../include/rotation.h"

int main(int argc, char** argv) {
    (void) argc; (void) argv; // suppress 'unused parameters' warning

    /* parameter check */
    if (argc != 3) {
        fprintf(stderr, "Not enough command line arguments. "
                        "The following arguments are required for the program to work correctly:"
                        "./image-transformer <source-image> <transformed-image>");
        return -1;
    }

    return rotate(argv[1], argv[2]);
}
