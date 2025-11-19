cmake_minimum_required(VERSION 3.16)
project(Lab5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(stack INTERFACE)
target_include_directories(stack INTERFACE ${CMAKE_SOURCE_DIR}/src)

add_executable(prog1 main.cpp)
target_link_libraries(prog1 PRIVATE stack)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(testing tests/test.cpp)
target_link_libraries(testing PRIVATE stack GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(testing)