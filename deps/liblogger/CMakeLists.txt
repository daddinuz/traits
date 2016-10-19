cmake_minimum_required(VERSION 2.8)
project(liblogger)

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
function(add_dependency TARGET PATH)
    file(GLOB FILES "${PATH}/*.c" "${PATH}/*.h")
    add_library("${TARGET}" "${FILES}")
endfunction()

set(ANSICOLOR_W32_PATH  "${DEPS_PATH}/ansicolor-w32")
add_dependency(ansicolor-w32    "${ANSICOLOR_W32_PATH}")

#####
# Library
###
add_library(logger "${SOURCE_FILES}")
target_include_directories(logger PRIVATE "${INCLUDE_PATH}" "${ANSICOLOR_W32_PATH}")
target_compile_definitions(logger PRIVATE NDEBUG=1 NCOLOR=1)
target_link_libraries(logger ansicolor-w32)

add_library(logger-debug "${SOURCE_FILES}")
target_include_directories(logger-debug PRIVATE "${INCLUDE_PATH}" "${ANSICOLOR_W32_PATH}")
target_compile_definitions(logger-debug PRIVATE)
target_link_libraries(logger-debug ansicolor-w32)

#####
# Examples
###
add_executable(logger-example "${EXAMPLE_PATH}/example.c")
target_include_directories(logger-example PRIVATE "${INCLUDE_PATH}")
target_link_libraries(logger-example logger-debug)
