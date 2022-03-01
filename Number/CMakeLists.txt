cmake_minimum_required(VERSION 3.21)
project(Number)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp Number.cpp)
add_library(Number ${SOURCE_FILES})
