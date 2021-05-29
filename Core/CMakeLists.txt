cmake_minimum_required(VERSION 3.1)

add_library(Plain-Core STATIC
  PLAObject.cpp
  PLAApp.cpp
  PLAInput.cpp
  PLAError.cpp
  PLAScene.cpp
  PLAStage.cpp
  PLAActor.cpp
  PLARenderer.cpp
  PLAResource.cpp
  PLAImageClip.cpp
  PLALayer/PLALayer.cpp
  PLALayer/PLALYRPoint.cpp
  PLALayer/PLALYRLine.cpp
  PLALayer/PLALYRRect.cpp
  PLALayer/PLALYRCircle.cpp)
