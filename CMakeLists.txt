cmake_minimum_required(VERSION 3.23)
project(blog C)

set(CMAKE_C_STANDARD 11)

add_executable(blog cssg.c str.c str.h)
