cmake_minimum_required(VERSION 3.27)
project(se-c-prog-sprintf-staff768 C)

set(CMAKE_C_STANDARD 17)
add_executable(expression main.c parsing.h struct.h help_function.h
        parsing.c
        help_function.c)