cmake_minimum_required(VERSION 3.1)

add_library(Plain-Core STATIC
  PLAObject.cpp
  PLAApp.cpp
  PLAInput.cpp
  PLAError.cpp
  PLAScene.cpp
  PLAStage.cpp
  PLAImage.cpp
  PLARenderer.cpp
  PLAResource.cpp
  PLAImageClip.cpp
  Actor/PLAActor.cpp
  Layer/PLALayer.cpp
  Layer/PLALYRPoint.cpp
  Layer/PLALYRLine.cpp
  Layer/PLALYRRect.cpp
  Layer/PLALYRCircle.cpp
  Layer/PLALYRTile.cpp)
