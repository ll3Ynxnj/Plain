// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/06/12.
//

#ifndef ANHR_PLAAGTMOTION_HPP
#define ANHR_PLAAGTMOTION_HPP


#include "PLAAGTTimeline.hpp"

class PLATMLMotion;

class PLAAGTMotion: public PLAAGTTimeline
{
  public:
    /// Agent is const method only.
    PLAAGTMotion() = default;
    explicit PLAAGTMotion(PLATMLMotion *aOwner);
    virtual ~PLAAGTMotion() noexcept;
};


#endif //ANHR_PLAAGTMOTION_HPP
