add_library(lab2_seqarray INTERFACE)
target_include_directories(lab2_seqarray INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lab2_core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../src/core)