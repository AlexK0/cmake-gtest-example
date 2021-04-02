cmake_minimum_required(VERSION 3.16)
project(hash_table)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(.)

add_compile_options(-O3 -march=native -Wall -Wextra -falign-functions=128)
add_executable(unittests hash-table-test.cpp)

target_link_libraries(unittests PRIVATE gtest gtest_main -lpthread)

add_executable(bench-insert hash-table-insert-bench.cpp)
target_link_libraries(bench-insert PRIVATE benchmark::benchmark)

add_executable(bench-insert-erase hash-table-insert-erase-bench.cpp)
target_link_libraries(bench-insert-erase PRIVATE benchmark::benchmark)
