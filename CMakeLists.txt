cmake_minimum_required(VERSION 3.12)

project(graduation_project VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_BUILD_TYPE "Release")

link_directories(AFTER ./lib)

aux_source_directory(./src SRC_LIST)
add_executable(out ${SRC_LIST})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

target_include_directories(out PUBLIC ./inc)

# target_link_libraries(out PUBLIC )