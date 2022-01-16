cmake_minimum_required(VERSION 3.21)
project(solution C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(solution
        include/bmp.h
        include/file.h
        include/image.h
        include/pixel.h
        include/rotation.h
        src/bmp.c
        src/file.c
        src/image.c
        src/main.c
        src/pixel.c
        src/rotation.c)
