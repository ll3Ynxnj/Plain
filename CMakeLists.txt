cmake_minimum_required(VERSION 2.8)

project(Plain CXX)

add_library(Plain
  PLAApp.cpp
  PLAErrorManager.cpp
  PLAStage.cpp
  PLADebug.cpp
  PLAError.cpp
  PLAActor.cpp
  PLARectActor.cpp
  PLACircleActor.cpp
  PLARenderer.cpp
)

# Testing framework must be built with the same settings as the product
add_subdirectory(Plain-Test)
