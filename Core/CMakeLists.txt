cmake_minimum_required(VERSION 3.1)

add_library(Plain-Core STATIC
  Class/PLAObject.cpp
  Class/PLAProperty.cpp
  Class/PLAApp.cpp
  Class/PLAError.cpp
  Class/PLAScene.cpp
  Class/PLAStage.cpp
  Class/PLAImage.cpp
  Class/PLARenderer.cpp
  Class/PLAResource.cpp
  Class/PLAImageClip.cpp
  Input/PLAInput.cpp
  Input/PLAInputState.cpp
  Input/PLAInputContext.cpp
  Input/PLAInputHandler.cpp
  Input/PLAInputManager.cpp
  Timeline/PLATimelineNode.cpp
  Timeline/PLATimeline.cpp
  Timeline/PLATimelineHolder.cpp
  Timeline/PLAMotionNode.cpp
  Timeline/PLAMotion.cpp
  Actor/PLAActor.cpp
  Layer/PLALayer.cpp
  Layer/PLALYRPoint.cpp
  Layer/PLALYRLine.cpp
  Layer/PLALYRRect.cpp
  Layer/PLALYRCircle.cpp
  Layer/PLALYRTile.cpp
  Agent/PLAAgent.cpp
  Agent/PLAAGTActor.cpp
  Agent/PLAAGTStage.cpp
  Agent/PLAAGTScene.cpp)
