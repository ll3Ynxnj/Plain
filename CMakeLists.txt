cmake_minimum_required(VERSION 3.12)

project(Plain CXX)

add_library(Plain STATIC Plain.cpp)

include_directories(Core)
include_directories(GLUT)
include_directories(Grain)

add_subdirectory(Core)
add_subdirectory(GLUT)
add_subdirectory(Grain)

# Testing framework must be built with the same settings as the product
add_subdirectory(Plain-Test)
