// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/09.
//

#ifndef PLAIN_PLAAGTMOTIONNODE_HPP
#define PLAIN_PLAAGTMOTIONNODE_HPP


#include "plain/core/agent/PLAAGTTimelineNode.hpp"

class PLATMLMotionNode;

class PLAAGTMotionNode: public PLAAGTTimelineNode
{
public:
  /// Agent is const method only.
  PLAAGTMotionNode() = delete;
  explicit PLAAGTMotionNode(PLATMLMotionNode *aOwner);
  virtual ~PLAAGTMotionNode() noexcept;

protected:
  const PLATMLMotionNode *GetMotionNode() const;
  PLATMLMotionNode *RefMotionNode() const;
};


#endif //PLAIN_PLAAGTMOTIONNODE_HPP
