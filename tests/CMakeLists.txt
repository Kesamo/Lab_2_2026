cmake_minimum_required(VERSION 3.15)
project(lab_2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(run_tests
    tests_SequenceArray.cpp
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/sequences
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/sequences/SequenceArray
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/sequences/SequenceList
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/utils 
)

enable_testing()


target_link_libraries(run_tests PRIVATE
    gtest_main
)

include(GoogleTest)

gtest_discover_tests(run_tests)

add_test(NAME run_tests COMMAND run_tests)