// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/12.
//

#ifndef PLAIN_PLAAGTMOTION_HPP
#define PLAIN_PLAAGTMOTION_HPP


#include "plain/core/agent/PLAAGTTimeline.hpp"

class PLATMLMotion;

class PLAAGTMotion: public PLAAGTTimeline
{
public:
  friend class PLAMotionHolder;

  /// Agent is const method only.
  PLAAGTMotion() = delete;
  explicit PLAAGTMotion(PLATMLMotion *aOwner);
  virtual ~PLAAGTMotion() noexcept;

protected:
  const PLATMLMotion *GetMotion() const;
  PLATMLMotion *RefMotion() const;
};


#endif //PLAIN_PLAAGTMOTION_HPP
