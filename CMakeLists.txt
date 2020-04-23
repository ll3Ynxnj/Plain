cmake_minimum_required(VERSION 2.8)

project(Plain CXX)

add_library(Plain
  PLAObj.cpp
  PLAApp.cpp
  PLADebug.cpp
  PLAError.cpp
  PLAStage.cpp
  PLAActor.cpp
  PLARectActor.cpp
  PLACircleActor.cpp
  PLARenderer.cpp
  PLAGLUTRenderer.cpp
  PLAErrorManager.cpp
)

# Testing framework must be built with the same settings as the product
add_subdirectory(Plain-Test)
