cmake_minimum_required(VERSION 3.14)
project(StandardDriver)

set(CMAKE_CXX_STANDARD 11)

add_executable(StandardDriver main.cpp Standard/Memory.h Standard/Memory.cpp)