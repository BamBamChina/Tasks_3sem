cmake_minimum_required(VERSION 3.20) # Проверка версии CMake.

set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


project(HelloWorld LANGUAGES CXX)

add_executable(HelloWorld main.cpp)
