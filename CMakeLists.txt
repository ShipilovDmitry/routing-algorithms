cmake_minimum_required(VERSION 3.30.0 FATAL_ERROR)

project("routing-algotithms" LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(dijkstra)
set(CMAKE_CXX_STANDARD 23)
