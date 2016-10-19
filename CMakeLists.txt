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
set(LOGGER_PATH         "${DEPS_PATH}/liblogger")
set(LOGGER_INCLUDE_PATH "${LOGGER_PATH}/include")
add_subdirectory("${LOGGER_PATH}")

#####
# Libraries
###
add_library(traits "${SOURCE_FILES}")
target_include_directories(traits PRIVATE "${INCLUDE_PATH}" "${LOGGER_INCLUDE_PATH}")
target_link_libraries(traits logger-debug)

#####
# Tests
###
add_executable(test-traits "${TEST_PATH}/test_traits.c")
target_include_directories(test-traits PRIVATE "${INCLUDE_PATH}" "${LOGGER_INCLUDE_PATH}")
target_link_libraries(test-traits traits)
