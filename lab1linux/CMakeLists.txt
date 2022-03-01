cmake_minimum_required(VERSION 3.21)
project(lab1linux)

set(CMAKE_CXX_STANDARD 14)
file(GLOB num_lib "lib/libNumber.a")
file(GLOB vec_lib "lib/libvectorLib.so")
add_executable(lab1linux main.cpp ${num_lib} ${vec_lib})
target_link_libraries(lab1linux ${num_lib} ${vec_lib})
include_directories(includes)
