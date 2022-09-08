cmake_minimum_required(VERSION 3.21)
project(MySpark)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(sources)

add_executable(Main main.cpp)

