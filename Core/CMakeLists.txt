cmake_minimum_required(VERSION 3.1)

#include_directories(Object)

add_library(Plain-Core STATIC
  Object/PLAObject.cpp
  Object/PLAApp.cpp
  Object/PLAError.cpp
  Object/PLAScene.cpp
  Object/PLAStage.cpp
  Object/PLAImage.cpp
  Object/PLARenderer.cpp
  Object/PLAResource.cpp
  Object/PLAImageClip.cpp

  Object/Input/PLAInput.cpp
  Object/Input/PLAInputState.cpp
  Object/Input/PLAInputContext.cpp
  Object/Input/PLAInputHandler.cpp
  Object/Input/PLAInputManager.cpp

  Object/Timeline/PLATimelineNode.cpp
  Object/Timeline/PLATimeline.cpp
  Object/Timeline/PLATimelineHolder.cpp
  Object/Timeline/PLAMotionNode.cpp
  Object/Timeline/PLAMotion.cpp

  Object/Actor/PLAActor.cpp

  Object/Layer/PLALayer.cpp
  Object/Layer/PLALYRPoint.cpp
  Object/Layer/PLALYRLine.cpp
  Object/Layer/PLALYRRect.cpp
  Object/Layer/PLALYRCircle.cpp
  Object/Layer/PLALYRTile.cpp

  Object/Agent/PLAAgent.cpp
  Object/Agent/PLAAGTActor.cpp
  Object/Agent/PLAAGTStage.cpp
  Object/Agent/PLAAGTScene.cpp

  Property/PLAProperty.cpp
  )
