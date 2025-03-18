cmake_minimum_required(VERSION 3.16)
project(Portfolio)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-std=c++23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure both main.cpp and Input.cpp are compiled
add_executable(Portfolio src/main.cpp 
                         src/Input.cpp 
                         src/Path.cpp 
                         src/Portfolio.cpp 
                         src/Table.cpp)
