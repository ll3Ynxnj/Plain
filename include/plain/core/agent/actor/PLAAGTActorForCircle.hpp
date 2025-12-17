// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#ifndef ANHR_PLAAGTACTORFORCIRCLE_HPP
#define ANHR_PLAAGTACTORFORCIRCLE_HPP


#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

class PLAOBJActor;

class PLAAGTActorForCircle : public PLAAGTActor
{
public:
  explicit PLAAGTActorForCircle(PLAOBJActor *aOwner);

  void SetStrokeColor(const PLAColor &aColor);
};


#endif //ANHR_PLAAGTACTORFORCIRCLE_HPP
