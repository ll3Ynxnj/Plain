// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#ifndef ANHR_PLAAGTACTORFORCIRCLE_HPP
#define ANHR_PLAAGTACTORFORCIRCLE_HPP


#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMStroke.hpp"

class PLAOBJActor;

class PLAAGTActorForCircle : public PLAAGTActor
{
public:
  explicit PLAAGTActorForCircle(PLAOBJActor *aOwner);

  void SetStroke(const PLAStroke &aStroke);
  void SetStrokeColor(const PLAColor &aColor);
  void SetStrokeWidth(PLAFloat aWidth);
  void SetStrokeJoin(PLAStroke::Join aJoin);
  void SetStrokeAlign(PLAStroke::Align aAlign);
};


#endif //ANHR_PLAAGTACTORFORCIRCLE_HPP
