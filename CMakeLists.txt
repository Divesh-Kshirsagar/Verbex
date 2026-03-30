# Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(verbex)

# Add subdirectories
add_subdirectory(cmake)
add_subdirectory(apps)
add_subdirectory(features)
add_subdirectory(core)
add_subdirectory(tests)