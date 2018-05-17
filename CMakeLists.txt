cmake_minimum_required(VERSION 3.8)
project(traits C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

# archive
include_directories(sources)

# Examples
include(examples/build.cmake)
