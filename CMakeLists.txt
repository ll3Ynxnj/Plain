cmake_minimum_required(VERSION 3.1)

project(Plain CXX)

add_subdirectory(Core)
add_subdirectory(GLUT)

include_directories(GLUT)
include_directories(Core)

# Testing framework must be built with the same settings as the product
add_subdirectory(Plain-Test)
