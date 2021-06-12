cmake_minimum_required(VERSION 3.16)
project(input_generator)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O3 -Wall -Wextra)

add_executable(input_generator input_generator.cpp)
