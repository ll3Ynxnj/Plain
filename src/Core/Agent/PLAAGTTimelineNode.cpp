// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/09.
//

#include "Core/Agent/PLAAGTTimelineNode.hpp"
#include "Core/Object/Timeline/PLAOBJTimelineNode.hpp"

PLAAGTTimelineNode::PLAAGTTimelineNode(PLAOBJTimelineNode *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTTimelineNode::~PLAAGTTimelineNode() noexcept
{

}

void PLAAGTTimelineNode::SetFunction(PLAFunctionCode::TimelineNode aKey,
                                     const std::function<void(
                                       PLAAGTTimelineNode)> &aFunc) const
{
  auto owner = this->RefTimelineNode();
  owner->SetFunction(aKey, aFunc);
}

const PLAOBJTimelineNode *PLAAGTTimelineNode::GetTimelineNode() const
{
  return static_cast<const PLAOBJTimelineNode *>(this->GetOwner());
}

PLAOBJTimelineNode *PLAAGTTimelineNode::RefTimelineNode() const
{
  return static_cast<PLAOBJTimelineNode *>(this->RefOwner());
}
