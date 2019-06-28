project(btk_library CXX)

set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-8")
cmake_minimum_required(VERSION 3.14.5)
find_package(Boost 1.4.8 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)

add_definitions(-DBTK)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")
add_compile_definitions()
enable_testing()

include_directories(${LIB_PATH})
include_directories(${BOOST_PATH})
add_subdirectory(test)
