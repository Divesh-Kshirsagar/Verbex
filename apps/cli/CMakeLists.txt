# CMakeLists.txt for CLI app
add_executable(cli main.cpp)

# Link libraries if needed
target_link_libraries(cli PRIVATE core features)