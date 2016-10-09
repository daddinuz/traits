cmake_minimum_required(VERSION 2.8)
project(libtraits)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

#####
# Defines
###
set(      PROJECT_PATH       "${PROJECT_SOURCE_DIR}")
set(      INCLUDE_PATH       "${PROJECT_PATH}/include")
set(      SOURCE_PATH        "${PROJECT_PATH}/src")
file(GLOB INCLUDE_FILES      "${INCLUDE_PATH}/*.h")
file(GLOB SOURCE_FILES       "${SOURCE_PATH}/*.c")

set(      EXAMPLE_PATH       "${PROJECT_PATH}/examples")
set(      TEST_PATH          "${PROJECT_PATH}/test")
set(      DEPS_PATH          "${PROJECT_PATH}/deps")

#####
# Dependencies
###


#####
# Libraries
###
add_library(traits "${INCLUDE_FILES}" "${SOURCE_FILES}")
target_include_directories(traits PRIVATE "${INCLUDE_PATH}")

#####
# Examples
###


#####
# Tests
###


#####
# Coverage
###
