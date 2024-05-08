cmake_minimum_required(VERSION 3.27)
project(Project5)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project5 main.cpp
        Graph.cpp
        Graph.h
        UnitTests.h)
