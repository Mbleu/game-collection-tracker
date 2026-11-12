cmake_minimum_required(VERSION 3.20)

project(game-collection-tracker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable 'game-collection-tracker' of program
add_executable(game-collection-tracker
    src/main.cpp
    src/Collection.cpp
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

# Create executable 'test_suite' to run tests
add_executable(test_suite
    tests/test_Collection.cpp
    src/Collection.cpp
    src/Game.cpp
)

# Add src/ as include for 'test_suite'
target_include_directories(test_suite PRIVATE src)

# Link the googletest library to 'test_suite'
target_link_libraries(test_suite PRIVATE GTest::gtest_main)

add_test(NAME test_suite COMMAND test_suite)