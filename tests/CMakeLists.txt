cmake_minimum_required(VERSION 3.15)

add_executable(run_tests
    tests_SequenceArray
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/sequences
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/sequences/SequenceArray
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/sequences/SequenceList
)

target_link_libraries(run_tests PRIVATE
    gtest_main
)
include(GoogleTest)
gtest_discover_tests(run_tests)