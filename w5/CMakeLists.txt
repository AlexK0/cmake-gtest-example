cmake_minimum_required(VERSION 3.16)
project(example)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(.)

add_compile_options(-O3 -Wall -Wextra)
add_executable(unittests
        alghoritms/algo1.cpp tests/algo1-test.cpp
        alghoritms/algo2.cpp tests/algo2-test.cpp)

target_link_libraries(unittests PRIVATE gtest gtest_main -lpthread)


add_executable(algo1-bench alghoritms/algo1.cpp benchmarks/algo1-bench.cpp)
target_link_libraries(algo1-bench PRIVATE benchmark::benchmark)

add_executable(algo2-bench alghoritms/algo2.cpp benchmarks/algo2-bench.cpp)
target_link_libraries(algo2-bench PRIVATE benchmark::benchmark)
