cmake_minimum_required(VERSION 3.0)
project(libtraits)


if (DISABLE_COLORS)
    message(STATUS "Using colors: false")
    set(NO_COLORS_FLAG 1)
else ()
    message(STATUS "Using colors: true")
    set(NO_COLORS_FLAG 0)
endif ()
set(CMAKE_C_FLAGS "-std=c89 -Wall -Wextra -DNCOLOR=${NO_COLORS_FLAG}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#####
# Project structure
###
set(PROJECT_PATH "${PROJECT_SOURCE_DIR}")
set(SOURCE_PATH "${PROJECT_PATH}/src")
file(GLOB SOURCE_FILES "${SOURCE_PATH}/*.c")

set(DEPS_PATH "${PROJECT_PATH}/deps")
set(TEST_PATH "${PROJECT_PATH}/test")
set(EXAMPLE_PATH "${PROJECT_PATH}/examples")

#####
# Dependencies
###
include_directories("${DEPS_PATH}/liblogger/src")
add_subdirectory("${DEPS_PATH}/liblogger")

#####
# Libraries
###
add_library(traits "${SOURCE_FILES}")
target_link_libraries(traits PRIVATE logger)

#####
# Tests
###
add_executable(test-traits "${TEST_PATH}/test_traits.c")
target_include_directories(test-traits PRIVATE "${SOURCE_PATH}")
target_link_libraries(test-traits PRIVATE traits)
