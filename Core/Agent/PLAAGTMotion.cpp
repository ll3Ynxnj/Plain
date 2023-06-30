// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/12.
//

#include "PLAAGTMotion.hpp"

#include "Object/Timeline/PLATMLMotion.hpp"

PLAAGTMotion::PLAAGTMotion(PLATMLMotion *aOwner) :
  PLAAGTTimeline(aOwner)
{

}

PLAAGTMotion::~PLAAGTMotion() noexcept
{

}

const PLATMLMotion *PLAAGTMotion::GetMotion() const
{
  return static_cast<const PLATMLMotion *>(this->GetOwner());
}

PLATMLMotion *PLAAGTMotion::RefMotion() const
{
  return static_cast<PLATMLMotion *>(this->RefOwner());
}
