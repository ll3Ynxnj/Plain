cmake_minimum_required(VERSION 3.1)

#include_directories(Object)

add_library(Plain-Core STATIC
  Object/PLAObject.cpp
  Object/PLAOBJApp.cpp
  Object/PLAOBJError.cpp
  Object/PLAOBJScene.cpp
  Object/PLAOBJStage.cpp
  Object/PLAOBJImage.cpp
  Object/PLAOBJRenderer.cpp
  Object/PLAOBJResource.cpp
  Object/PLAOBJImageClip.cpp

  Object/Input/PLAInput.cpp
  Object/Input/PLAInputState.cpp
  Object/Input/PLAInputContext.cpp
  Object/Input/PLAInputHandler.cpp
  Object/Input/PLAInputManager.cpp

  Object/Timeline/PLAOBJTimelineNode.cpp
  Object/Timeline/PLAOBJTimeline.cpp
  Object/Timeline/PLATimelineHolder.cpp
  Object/Timeline/PLATMLMotionNode.cpp
  Object/Timeline/PLATMLMotion.cpp

  Object/Actor/PLAOBJActor.cpp

  Object/Layer/PLAOBJLayer.cpp
  Object/Layer/PLALYRPoint.cpp
  Object/Layer/PLALYRLine.cpp
  Object/Layer/PLALYRRect.cpp
  Object/Layer/PLALYRCircle.cpp
  Object/Layer/PLALYRTile.cpp

  Object/Agent/PLAOBJAgent.cpp
  Object/Agent/PLAAGTActor.cpp
  Object/Agent/PLAAGTStage.cpp
  Object/Agent/PLAAGTScene.cpp

  Property/PLAProperty.cpp
  )
