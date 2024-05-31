// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/12.
//

#include "plain/core/agent/PLAAGTTimeline.hpp"
#include "plain/core/agent/PLAAGTTimelineNode.hpp"

#include "plain/core/object/timeline/PLAOBJTimeline.hpp"

PLAAGTTimeline::PLAAGTTimeline(PLAOBJTimeline *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTTimeline::~PLAAGTTimeline() noexcept
{

}

void PLAAGTTimeline::AddNode(const PLAAGTTimelineNode &aAgent)
{
  PLAId nodeId = aAgent.GetObjectId();
  PLAOBJTimelineNode *node = PLAOBJTimelineNode::Object(nodeId);
  auto timeline = this->RefTimeline();
  timeline->AddNode(node);
}

void PLAAGTTimeline::SetFunction(PLAFunctionCode::Timeline aKey,
                                 const std::function<void(PLAAGTTimeline)> &aFunc) const
{
  auto owner = this->RefTimeline();
  owner->SetFunction(aKey, aFunc);
}

const PLAOBJTimeline *PLAAGTTimeline::GetTimeline() const
{
  return static_cast<const PLAOBJTimeline *>(this->GetOwner());
}

PLAOBJTimeline *PLAAGTTimeline::RefTimeline() const
{
  return static_cast<PLAOBJTimeline *>(this->RefOwner());
}
