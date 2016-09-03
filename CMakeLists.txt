cmake_minimum_required(VERSION 3.6)
project(nintendo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Polynomial.cpp Polynomial.h nintendo.h)
add_executable(nintendo ${SOURCE_FILES})