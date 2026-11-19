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

include(FetchContent)

# Fetch json parser
FetchContent_Declare(
    nlohmannjson
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    URL_HASH SHA256=42f6e95cad6ec532fd372391373363b62a14af6d771056dbfc86160e6dfff7aa
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(nlohmannjson)

# Build executable 'game-collection-tracker' using source files
add_executable(game-collection-tracker
    src/main.cpp
    src/Collection.cpp
    src/UI.cpp
    src/Game.cpp
    src/FileManager.cpp
)

# Link the nlohmann json library to 'game-collection-tracker'
target_link_libraries(game-collection-tracker PRIVATE nlohmann_json::nlohmann_json)

# Enable CTest
enable_testing()

# Fetch googletest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/releases/download/v1.18.0/googletest-1.18.0.tar.gz
    URL_HASH SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

# Build executable 'test-game-collection-tracker' from test source files
add_executable(test-game-collection-tracker
    tests/test_Collection.cpp
    src/Collection.cpp
    src/UI.cpp
    src/Game.cpp
    src/FileManager.cpp
)

# Add src/ as a directory in which 'test-game-collection-tracker's #includes can find .h files
target_include_directories(test-game-collection-tracker PRIVATE src)

# Link the googletest library to 'test-game-collection-tracker'
target_link_libraries(test-game-collection-tracker PRIVATE GTest::gtest_main nlohmann_json::nlohmann_json)

# Add googletest commands to cmake
include(GoogleTest)
# Find tests in the googletest format and create cmake tests for them
gtest_discover_tests(test-game-collection-tracker)