cmake_minimum_required(VERSION 3.20)
project(lirs_cache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

find_package(GTest REQUIRED)

add_executable(lirs src/lirs.cc)
target_include_directories(lirs PRIVATE include)

add_executable(tests tests/tests.cc)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)

gtest_discover_tests(tests)
