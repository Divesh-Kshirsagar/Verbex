# CMakeLists.txt for AST
add_library(ast ast.cpp)

target_include_directories(ast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})