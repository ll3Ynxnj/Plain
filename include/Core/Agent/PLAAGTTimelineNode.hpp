// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/09.
//

#ifndef ANHR_PLAAGTTIMELINENODE_HPP
#define ANHR_PLAAGTTIMELINENODE_HPP


#include <functional>
#include "Core/Agent/PLAAgent.hpp"
#include "Core/PLAFunctionCode.hpp"

class PLAOBJTimelineNode;

class PLAAGTTimelineNode: public PLAAgent
{
public:
  /// Agent is const method only.
  PLAAGTTimelineNode() = delete;
  explicit PLAAGTTimelineNode(PLAOBJTimelineNode *aOwner);
  virtual ~PLAAGTTimelineNode() noexcept;

  void SetFunction(PLAFunctionCode::TimelineNode aKey,
                   const std::function<void(PLAAGTTimelineNode)> &aFunc) const;

protected:
  const PLAOBJTimelineNode *GetTimelineNode() const;
  PLAOBJTimelineNode *RefTimelineNode() const;
};


#endif //ANHR_PLAAGTTIMELINENODE_HPP
