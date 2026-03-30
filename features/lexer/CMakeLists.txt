# CMakeLists.txt for lexer
add_library(lexer lexer.cpp)

# Include directories
target_include_directories(lexer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})