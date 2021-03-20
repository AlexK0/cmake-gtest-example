cmake_minimum_required(VERSION 3.16)
project(example)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(.)

add_compile_options(-O3 -Wall -Wextra -falign-functions=128)
add_executable(unittests
        tests/algo1-test.cpp alghoritms/algo1.cpp
        tests/algo2-test.cpp alghoritms/algo2.cpp
        tests/algo3-test.cpp
        tests/algo4-test.cpp alghoritms/algo4.cpp
        tests/algo5-test.cpp alghoritms/algo5.cpp
        tests/algo6-test.cpp alghoritms/algo6.cpp)

target_link_libraries(unittests PRIVATE gtest gtest_main -lpthread)


add_executable(algo1-bench alghoritms/algo1.cpp benchmarks/algo1-bench.cpp)
target_link_libraries(algo1-bench PRIVATE benchmark::benchmark)

add_executable(algo2-bench alghoritms/algo2.cpp benchmarks/algo2-bench.cpp)
target_link_libraries(algo2-bench PRIVATE benchmark::benchmark)

add_executable(algo3-bench benchmarks/algo3-bench.cpp)
target_link_libraries(algo3-bench PRIVATE benchmark::benchmark)

add_executable(algo4-bench alghoritms/algo4.cpp benchmarks/algo4-bench.cpp)
target_link_libraries(algo4-bench PRIVATE benchmark::benchmark)

add_executable(algo5-bench alghoritms/algo5.cpp benchmarks/algo5-bench.cpp)
target_link_libraries(algo5-bench PRIVATE benchmark::benchmark)

add_executable(algo6-bench alghoritms/algo6.cpp benchmarks/algo6-bench.cpp)
target_link_libraries(algo6-bench PRIVATE benchmark::benchmark)