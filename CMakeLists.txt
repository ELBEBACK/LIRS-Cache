cmake_minimum_required(VERSION 3.20)
project(ideal_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

include_directories(PRIVATE include)

add_executable(oracle src/oracle.cc)
add_executable(lirs src/lirs.cc)

add_executable(lirsTests tests/lirsTests.cc)
add_executable(optTests tests/optTests.cc)

target_link_libraries(lirsTests GTest::gtest_main GTest::gtest pthread)
target_link_libraries(optTests GTest::gtest_main GTest::gtest pthread)

gtest_discover_tests(lirsTests)
gtest_discover_tests(optTests)