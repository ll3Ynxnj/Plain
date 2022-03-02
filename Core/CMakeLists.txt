cmake_minimum_required(VERSION 3.1)

add_library(Plain-Core STATIC
  PLAObject.cpp
  PLAProperty.cpp
  PLAApp.cpp
  PLAError.cpp
  PLAScene.cpp
  PLAStage.cpp
  PLAImage.cpp
  PLARenderer.cpp
  PLAResource.cpp
  PLAImageClip.cpp
  Input/PLAInput.cpp
  Node/PLANode.cpp
  Node/PLANodeThread.cpp
  Node/PLANodeHolder.cpp
  Node/PLAMotion.cpp
  Node/PLAMotionThread.cpp
  Actor/PLAActor.cpp
  Layer/PLALayer.cpp
  Layer/PLALYRPoint.cpp
  Layer/PLALYRLine.cpp
  Layer/PLALYRRect.cpp
  Layer/PLALYRCircle.cpp
  Layer/PLALYRTile.cpp)
