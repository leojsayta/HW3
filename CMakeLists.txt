cmake_minimum_required(VERSION 2.8.4)
project(HW3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    HW3Classes.cpp
    HW3Classes.h
    main.cpp
    p054_poker.txt)

add_executable(HW3 ${SOURCE_FILES})