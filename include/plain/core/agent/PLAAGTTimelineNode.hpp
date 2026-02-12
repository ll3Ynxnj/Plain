// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/09.
//

#ifndef ANHR_PLAAGTTIMELINENODE_HPP
#define ANHR_PLAAGTTIMELINENODE_HPP


#include <functional>
#include "plain/core/agent/PLAAgent.hpp"
#include "plain/core/PLAFunctionCode.hpp"
#include "plain/core/primitive/PLAPRMType.hpp"

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

  /// Get current interpolated value from a Value motion node
  PLAFloat GetValue() const;

protected:
  const PLAOBJTimelineNode *GetTimelineNode() const;
  PLAOBJTimelineNode *RefTimelineNode() const;
};


#endif //ANHR_PLAAGTTIMELINENODE_HPP
