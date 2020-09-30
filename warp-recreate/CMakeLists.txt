cmake_minimum_required(VERSION 3.16)
project(warper)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(Catch_tests)
add_executable(warper Warper.cpp Warper.h main.cpp)