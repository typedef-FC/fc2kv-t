# cmake settings
cmake_minimum_required(VERSION 3.29)

# project
project(fc2kv-t)

# settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# executables
add_executable(fc2kv-t main.cpp
        dependencies/include/fc2.hpp)

# include
target_include_directories( fc2kv-t PRIVATE
        "${CMAKE_SOURCE_DIR}/dependencies/include"
)