# CMakeLists.txt for diagnostics
add_library(diagnostics diagnostic.cpp)

target_include_directories(diagnostics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})