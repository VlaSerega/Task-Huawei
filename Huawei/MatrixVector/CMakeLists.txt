cmake_minimum_required(VERSION 3.17)
project(MatrixVector C)

set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_C_STANDARD 11)

add_executable(MatrixVector main.c dgemm.c)