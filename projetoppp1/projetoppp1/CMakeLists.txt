cmake_minimum_required(VERSION 3.17)
project(projetoppp1 C)

set(CMAKE_C_STANDARD 11)

add_executable(projetoppp1 main.c auxproj1.c)

add_compile_options(-Wall -Wextra)