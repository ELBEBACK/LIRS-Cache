cmake_minimum_required(VERSION 3.20)
project(ideal_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

include_directories(PRIVATE include)

add_executable(oracle src/oracle.cc)
add_executable(lirs src/lirs.cc)

add_executable(cacheTests
    tests/lirsTests.cc
    tests/optTests.cc
)

target_link_libraries(cacheTests GTest::gtest_main GTest::gtest pthread)

gtest_discover_tests(cacheTests)