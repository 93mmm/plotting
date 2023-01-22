cmake_minimum_required(VERSION 3.16)

project(Plotting)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CPP_COMPILER clang)

set(PROJECT_SOURCES
        src/main.cpp
        include/exprtk.hpp
        include/header.hpp
)

add_executable(plot ${PROJECT_SOURCES})
