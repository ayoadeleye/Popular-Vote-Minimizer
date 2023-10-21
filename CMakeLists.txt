cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled app.c
        MinPopVote.c
        MinPopVote.h
        test.c)
