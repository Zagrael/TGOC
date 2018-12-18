cmake_minimum_required(VERSION 3.13)
project(Challenge)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(Challenge main.cpp ant.cpp ant.h problem.cpp problem.h antsystem.cpp antsystem.h antexception.h QAP.cpp QAP.h)