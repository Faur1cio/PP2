cmake_minimum_required(VERSION 3.22)
project(PP2 C)

set(CMAKE_C_STANDARD 99)

add_executable(PP2 main.c TasksGraph.c TasksGraph.h docsTree.c docsTree.h resourcesList.c resourcesList.h)
