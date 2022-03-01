cmake_minimum_required(VERSION 3.21)
project(Vector)

set(CMAKE_CXX_STANDARD 14)
set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(GLOB num_lib "lib/libNumber.a")
include_directories(includes)
add_library( vectorLib SHARED
        Vector.cpp Vector.h)
