project(btk_library CXX)

set(CMAKE_CXX_COMPILER $ENV{BUILD_CMD})
cmake_minimum_required(VERSION 3.14.5)
find_package(Boost 1.4.8 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)

add_definitions(-DBTK)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -std=c++17")
add_compile_definitions("BTK")
enable_testing()

include_directories($ENV{LIB_PATH})
include_directories($ENV{BOOST_PATH})
add_subdirectory(test)
