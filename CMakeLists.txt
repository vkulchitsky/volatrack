cmake_minimum_required(VERSION 3.5)

project(Volatrack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Volatrack main.cpp physics/sphere.cpp physics/volatile.cpp)
