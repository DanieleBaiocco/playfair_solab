cmake_minimum_required(VERSION 3.15)
project(playfair C)

set(CMAKE_C_STANDARD 99)

add_executable(playfair main.c playfair.c playfair.h deallocate.h deallocate.c utility.h utility.c)

