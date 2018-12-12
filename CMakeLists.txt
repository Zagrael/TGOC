cmake_minimum_required(VERSION 3.13)
project(Challenge)

set(CMAKE_CXX_STANDARD 17)

add_executable(Challenge main.cpp ant.cpp ant.h problem.cpp problem.h antsystem.cpp antsystem.h antexception.h)