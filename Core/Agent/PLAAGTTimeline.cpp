// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/12.
//

#include "PLAAGTTimeline.hpp"
#include "PLAAGTTimelineNode.hpp"

#include "Object/Timeline/PLAOBJTimeline.hpp"

PLAAGTTimeline::PLAAGTTimeline(PLAOBJTimeline *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTTimeline::~PLAAGTTimeline() noexcept
{

}

const PLAOBJTimeline *PLAAGTTimeline::GetTimeline() const
{
  return static_cast<const PLAOBJTimeline *>(this->GetOwner());
}

PLAOBJTimeline *PLAAGTTimeline::RefTimeline() const
{
  return static_cast<PLAOBJTimeline *>(this->RefOwner());
}

void PLAAGTTimeline::AddNode(const PLAAGTTimelineNode &aAgent)
{
  PLAId nodeId = aAgent.GetObjectId();
  PLAOBJTimelineNode *node = PLAOBJTimelineNode::Object(nodeId);
  auto timeline = this->RefTimeline();
  timeline->AddNode(node);
}
