cmake_minimum_required(VERSION 3.20)

project(game-collection-tracker)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game-collection-tracker
    src/main.cpp
    src/Collection.cpp
    src/Game.cpp
)

enable_testing()

add_executable(test_suite
    tests/test_main.cpp
    tests/test_Game.cpp
    tests/test_Collection.cpp
    src/Collection.cpp
    src/Game.cpp
)

target_include_directories(test_suite PRIVATE src)

add_test(NAME test_suite COMMAND test_suite)