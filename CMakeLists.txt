cmake_minimum_required(VERSION 3.26)
project(Projeto1DA)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto1DA
        src/main.cpp
        src/parsing/parsing.cpp
        src/parsing/parsing.h
        src/Menu/Menu.h
        src/Menu/Menu.cpp
        src/graph/Info.cpp
        src/graph/Info.h)
