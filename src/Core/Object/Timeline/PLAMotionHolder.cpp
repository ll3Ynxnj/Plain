// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/20.
//

#include "Core/Object/Timeline/PLAMotionHolder.hpp"
#include "Core/Object/Timeline/PLATMLMotion.hpp"
#include "Core/Agent/PLAAGTMotion.hpp"

/*
void PLAMotionHolder::AddMotionThread(PLATMLMotion *aMotion)
{
  auto timeline = this->GetTimeline();
  if (timeline)
  {
    GRA_TRACE("%s", timeline->GetObjectName().c_str());
  }
  this->AddTimelineThread(aMotion);
}
 */

const PLATMLMotion *PLAMotionHolder::GetMotion() const
{
  return static_cast<const PLATMLMotion *>(this->GetTimeline());
}

void PLAMotionHolder::AddMotionThread(PLATMLMotion *aThread)
{
  this->AddTimelineThread(aThread);
}

void PLAMotionHolder::AddMotionThread(const PLAAGTMotion &aAgent)
{
  auto thread = aAgent.RefMotion();
  this->AddMotionThread(thread);
}
