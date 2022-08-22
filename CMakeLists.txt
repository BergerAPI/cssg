cmake_minimum_required(VERSION 3.23)
project(cssg CXX)

set(CMAKE_CXX_STANDARD 23)

add_executable(cssg
        src/cssg.cpp src/str.cpp src/str.h
        src/file.cpp src/file.h src/parameter.cpp
        src/parameter.h)
