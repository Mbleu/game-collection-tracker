# Abort this script if min version of cmake not installed
cmake_minimum_required(VERSION 3.20)

# Name my project
project(game-collection-tracker)

# Announce min standard of C++ that the code requires compiler to have
set(CMAKE_CXX_STANDARD 23)
# Abort this script if min standard not met
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Do not allow compiler specific non-standard C++ features
set(CMAKE_CXX_EXTENSIONS OFF)

# Build executable 'game-collection-tracker' using source files
add_executable(game-collection-tracker
    src/main.cpp
    src/Collection.cpp
    src/UI.cpp
    src/Game.cpp
)

# Enable CTest
enable_testing()

# Fetch googletest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.18.0.zip
    URL_HASH SHA256=63b9c77751a5b8f492486005f67533fdc58682b67476fcb91650be5958d5195a
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Build executable 'test_suite' from test source files
add_executable(test_suite
    tests/test_Collection.cpp
    src/Collection.cpp
    src/UI.cpp
    src/Game.cpp
)

# Add src/ as a directory in which 'test_suite's #includes can find .h files
target_include_directories(test_suite PRIVATE src)

# Link the googletest library to 'test_suite'
target_link_libraries(test_suite PRIVATE GTest::gtest_main)

# Add googletest commands to cmake
include(GoogleTest)
# Find tests in the googletest format and create cmake tests for them
gtest_discover_tests(test_suite)