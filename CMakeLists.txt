cmake_minimum_required(VERSION 3.23)
project(cssg C)

set(CMAKE_C_STANDARD 11)

add_executable(cssg src/cssg.c src/str.c src/str.h src/file.c src/file.h)
