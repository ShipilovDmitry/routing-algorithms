cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project("routing-algotithms" LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(dijkstra)
add_subdirectory(redblobgames)

set(CMAKE_CXX_STANDARD 23)
