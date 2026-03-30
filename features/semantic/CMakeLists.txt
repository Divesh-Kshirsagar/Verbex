# CMakeLists.txt for semantic analyzer
add_library(semantic analyzer.cpp)

target_include_directories(semantic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})