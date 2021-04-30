cmake_minimum_required(VERSION 3.16)
project(example)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O3 -march=native -Wall -Wextra)
add_executable(paralel_unique_example paralel_unique.cpp)
add_executable(example main.cpp)

target_link_libraries(paralel_unique_example PRIVATE -lpthread)
target_link_libraries(example PRIVATE -lpthread)