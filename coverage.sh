#!/usr/bin/env bash

#####
# Exit on error
###
set -e

#####
# Variables
###
SCRIPT_PATH=$(readlink -f $(dirname "$0"))
BIN_PATH="$SCRIPT_PATH/bin"
TEST_PATH="$SCRIPT_PATH/test"
BUILD_PATH="$SCRIPT_PATH/build"
SOURCE_PATH="$SCRIPT_PATH/src"
COVERAGE_PATH="$SCRIPT_PATH/coverage"
HTML_COVERAGE_PATH="$COVERAGE_PATH/html"
CMAKE_GENERATED_PATH="$BUILD_PATH/CMakeFiles"

#####
# Build the project
###
mkdir -p "$BUILD_PATH"
cd "$BUILD_PATH"
cmake ..
make

#####
# Extract coverage
###
mkdir -p "$COVERAGE_PATH"
echo -e "\nRunning tests..."
for i in "$BIN_PATH"/coverage-*; do
    echo "  - Running: $i";
    "$i"
done
echo
find "$CMAKE_GENERATED_PATH/" -name \*.gcda -exec cp {} "$COVERAGE_PATH" \;
find "$CMAKE_GENERATED_PATH/" -name \*.gcno -exec cp {} "$COVERAGE_PATH" \;
lcov --capture --directory "$COVERAGE_PATH" --output-file "$COVERAGE_PATH/coverage.info"

#####
# Generate HTML output
###
mkdir -p "$HTML_COVERAGE_PATH"
echo "Generating HTML output in: $HTML_COVERAGE_PATH..."
genhtml "$COVERAGE_PATH/coverage.info" --output-directory "$HTML_COVERAGE_PATH"
echo -e "\nSuccess\n  - Go to: 'file://$HTML_COVERAGE_PATH/index.html' to see the coverage!"
