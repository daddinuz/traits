cmake_minimum_required(VERSION 3.5)
project(traits)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pedantic")
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wcast-align -Wbad-function-cast")
endif ()

#####
# Woring direcotries
###
include_directories(${PROJECT_SOURCE_DIR}/src)

#####
# Examples
###
file(GLOB EXAMPLE_SOURCES ${PROJECT_SOURCE_DIR}/examples/*.c)
foreach (source_file ${EXAMPLE_SOURCES})
    get_filename_component(target ${source_file} NAME_WE)
    add_executable(${target} src/traits.h ${source_file})
endforeach (source_file ${EXAMPLE_SOURCES})
