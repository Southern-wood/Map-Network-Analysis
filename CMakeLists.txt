cmake_minimum_required(VERSION 3.25)
project(map)

set(CMAKE_CXX_STANDARD 17)

add_executable(map main.cpp Graph.h
        Graph.cpp
        Login.cpp
        Login.h Menu.cpp Menu.h)
