cmake_minimum_required(VERSION 3.10)
project(ideal_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

add_executable(oracle src/oracle.cc)
target_include_directories(oracle PRIVATE include)

add_executable(tests tests/tests.cc)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests GTest::gtest_main GTest::gtest pthread)

gtest_discover_tests(tests)
