// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/09.
//

#ifndef ANHR_PLAAGTMOTIONNODE_HPP
#define ANHR_PLAAGTMOTIONNODE_HPP


#include "Core/Agent/PLAAGTTimelineNode.hpp"

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


#endif //ANHR_PLAAGTMOTIONNODE_HPP
