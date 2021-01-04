cmake_minimum_required(VERSION 3.1)

project(Plain CXX)

add_library(Plain
  PLAObject.cpp
  PLAApp.cpp
  PLAInput.cpp
  PLAError.cpp
  PLAStage.cpp
  PLAActor.cpp
  PLAShape.cpp
  PLAStyle.cpp
  PLARenderer.cpp
  PLACollision.cpp
)

# Testing framework must be built with the same settings as the product
add_subdirectory(Plain-Test)
