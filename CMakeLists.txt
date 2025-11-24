cmake_minimum_required(VERSION 3.20)
project(ideal_cache LANGUAGES CXX)

enable_testing()

find_package(GTest REQUIRED)

add_library(lirs_lib INTERFACE)
target_include_directories(lirs_lib INTERFACE include)
target_compile_features(lirs_lib INTERFACE cxx_std_23)

add_library(oracle_lib INTERFACE)  
target_include_directories(oracle_lib INTERFACE include)
target_compile_features(oracle_lib INTERFACE cxx_std_17)

add_executable(oracle src/oracle.cc)
target_link_libraries(oracle oracle_lib)

add_executable(lirs src/lirs.cc)
target_link_libraries(lirs lirs_lib)

add_executable(cacheTests
    tests/lirsTests.cc
    tests/optTests.cc
)

target_link_libraries(cacheTests
    GTest::gtest_main 
    GTest::gtest 
    pthread
    lirs_lib
    oracle_lib
)

gtest_discover_tests(cacheTests)