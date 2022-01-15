cmake_minimum_required(VERSION 3.21)
project(solution C)

set(CMAKE_C_STANDARD 11)

include_directories(include)

add_executable(solution
        include/file.h
        include/image.h
        include/pixel.h
        src/file.c
        src/image.c
        src/main.c include/bmp.h src/bmp.c src/pixel.c)
