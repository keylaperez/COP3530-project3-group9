cmake_minimum_required(VERSION 3.22)
project(COP3530-Project3-group9)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Main
        src/main.cpp
        src/movieHashMap.cpp
)