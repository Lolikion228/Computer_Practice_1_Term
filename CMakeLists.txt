cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)



add_executable(untitled1
        main.c
        big_int/big_int.h
        big_int/big_int.c
        lib/lib.c
        lib/lib.h)
