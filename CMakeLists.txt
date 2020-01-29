project(btk_library CXX)

cmake_minimum_required(VERSION 3.12.4)
find_package(Boost 1.72.0 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)

add_definitions(-DBTK)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Werror -std=c++14")
add_compile_definitions("BTK")
enable_testing()

include_directories($ENV{BOOST_PATH})
include_directories(src)
add_subdirectory(test)
