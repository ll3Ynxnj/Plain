cmake_minimum_required(VERSION 2.8)

project(Plain CXX)

add_library(Plain
  PLADebug.cpp
  PLARenderer.cpp
  PLARenderingManager.cpp
  PLAErrorManager.cpp
  PLAError.cpp
  PLAStageManager.cpp
  PLAActor.cpp
  PLARectActor.cpp
  PLACircleActor.cpp
)

# Testing framework must be built with the same settings as the product
add_subdirectory(Plain-Test)
