cmake_minimum_required(VERSION 3.30)
project(TO_DOList C)

set(CMAKE_C_STANDARD 11)

add_executable(TO_DOList main.c
        functions.c
        functions.h)
