cmake_minimum_required(VERSION 3.17)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Assignment_2
        src/main.cpp src/solver.cpp src/solver.h src/stack.cpp src/stack.h src/cursor.cpp src/cursor.h)
