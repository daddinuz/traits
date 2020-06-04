cmake_minimum_required(VERSION 3.10)
project(traits C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror -pedantic-errors")

# deps
include_directories(deps)

# archive
include_directories(sources)

# examples
include(examples/build.cmake)

# tests
include(tests/build.cmake)
