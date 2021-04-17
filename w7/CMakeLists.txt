cmake_minimum_required(VERSION 3.16)
project(hash_table)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(.)

#add_compile_options(-O3 -march=native -Wall -Wextra -falign-functions=128 -fsanitize=address)
add_compile_options(-O0 -ggdb3 -march=native -Wall -Wextra -falign-functions=128)
add_executable(unittests-hash-table hash-table-test.cpp)
add_executable(unittests-magic-compare magic-compare-test.cpp magic-compare.cpp)

#target_link_libraries(unittests-hash-table PRIVATE gtest gtest_main -lpthread -fsanitize=address)
target_link_libraries(unittests-hash-table PRIVATE gtest gtest_main -lpthread)
target_link_libraries(unittests-magic-compare PRIVATE gtest gtest_main -lpthread)