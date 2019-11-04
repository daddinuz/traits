cmake_minimum_required(VERSION 3.10)
project(traits C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -Wpedantic -pedantic-errors")

# archive
include_directories(sources)

# Examples
include(examples/build.cmake)
