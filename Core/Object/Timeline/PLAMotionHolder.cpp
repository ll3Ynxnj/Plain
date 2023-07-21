// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/20.
//

#include "PLAMotionHolder.hpp"
#include "PLATMLMotion.hpp"

const PLATMLMotion *PLAMotionHolder::GetMotion() const
{
  auto timeline = this->GetTimeline();
  if (timeline)
  {
    GRA_TRACE("%s", timeline->GetObjectName().c_str());
  }
  return static_cast<const PLATMLMotion *>(this->GetTimeline());
}