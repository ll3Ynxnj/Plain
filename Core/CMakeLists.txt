cmake_minimum_required(VERSION 3.12)

#include_directories(Object)

add_library(Plain-Core STATIC
  Object/PLAObject.cpp
  App/PLAApp.cpp
  Object/PLAOBJError.cpp
  Object/PLAOBJState.cpp
  Object/PLAOBJStage.cpp
  Object/PLAOBJScene.cpp
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
  Object/Timeline/PLAMotionHolder.cpp
  Object/Timeline/PLATMLMotionNode.cpp
  Object/Timeline/PLATMLMotion.cpp

  Object/Phase/PLAOBJPhase.cpp

  Object/Model/PLAOBJModel.cpp

  Object/Actor/PLAOBJActor.cpp

  Object/Layer/PLAOBJLayer.cpp
  Object/Layer/PLALYRPoint.cpp
  Object/Layer/PLALYRLine.cpp
  Object/Layer/PLALYRRect.cpp
  Object/Layer/PLALYRCircle.cpp
  Object/Layer/PLALYRTile.cpp

  Agent/PLAAgent.cpp
  Agent/PLAAGTPhase.cpp
  Agent/PLAAGTModel.cpp
  Agent/Actor/PLAAGTActor.cpp
  Agent/Actor/PLAAGTActorForRect.cpp
  Agent/Actor/PLAAGTActorForCircle.cpp
  Agent/Actor/PLAAGTActorForTile.cpp
  Agent/PLAAGTScene.cpp
  Agent/PLAAGTState.cpp
  Agent/PLAAGTStage.cpp
  Agent/PLAAGTTimeline.cpp
  Agent/PLAAGTTimelineNode.cpp
  Agent/PLAAGTMotion.cpp
  Agent/PLAAGTMotionNode.cpp
  Agent/PLAAGTImageClip.cpp

  Property/PLAProperty.cpp
)
