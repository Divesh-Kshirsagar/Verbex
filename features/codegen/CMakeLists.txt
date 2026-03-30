# CMakeLists.txt for code generation
add_library(codegen codegen.cpp)

target_include_directories(codegen PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})