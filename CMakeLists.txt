cmake_minimum_required(VERSION 3.22)
project(COP3530-Project3-group9)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(COP3530_Project3
        main.cpp
        movieHashMap.h
        movieHashMap.cpp
)