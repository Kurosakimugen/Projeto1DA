cmake_minimum_required(VERSION 3.26)
project(Projeto1DA)

set(CMAKE_CXX_STANDARD 14)

add_executable(Projeto1DA
        src/main.cpp
        src/menu/Menu.h
        src/menu/Menu.cpp
        src/graph/Info.cpp
        src/graph/Info.h
        src/graph/Network.h
        src/graph/Network.cpp
        src/graph/Vertex.h
        src/graph/Vertex.cpp
        src/graph/Edge.h
        src/graph/Edge.cpp
)
