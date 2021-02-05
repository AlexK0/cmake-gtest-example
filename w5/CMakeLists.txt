cmake_minimum_required(VERSION 3.16)
project(example)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(src)

#add_executable(unittests
#        tests/tests-math.cpp src/my-math.cpp
#        tests/test-string-observer.cpp src/string-observer.cpp
#        tests/test-observed-string.cpp src/observed-string.cpp)
#
#target_link_libraries(unittests PRIVATE gtest gtest_main -lpthread)


add_executable(benchmarks
        benchmarks/bench-example.cpp)
target_link_libraries(benchmarks PRIVATE benchmark::benchmark)
