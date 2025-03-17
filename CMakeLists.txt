
cmake_minimum_required(VERSION 3.16)
project(Portfolio)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-std=c++23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Portfolio src/main.cpp)