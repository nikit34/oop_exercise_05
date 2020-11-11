cmake_minimum_required(VERSION 3.5)

project(lab5)

add_executable(lab5 main.cpp)

set_property(TARGET lab5 PROPERTY CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
