// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/09.
//

#include "Core/Agent/PLAAGTMotionNode.hpp"
#include "Core/Object/Timeline/PLATMLMotionNode.hpp"

PLAAGTMotionNode::PLAAGTMotionNode(PLATMLMotionNode *aOwner) :
  PLAAGTTimelineNode(aOwner)
{

}

PLAAGTMotionNode::~PLAAGTMotionNode() noexcept
{

}

const PLATMLMotionNode *PLAAGTMotionNode::GetMotionNode() const
{
  return static_cast<const PLATMLMotionNode *>(this->GetOwner());
}

PLATMLMotionNode *PLAAGTMotionNode::RefMotionNode() const
{
  return static_cast<PLATMLMotionNode *>(this->RefOwner());
}
