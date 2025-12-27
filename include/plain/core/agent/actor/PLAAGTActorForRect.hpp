// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#ifndef ANHR_PLAAGTACTORFORRECT_HPP
#define ANHR_PLAAGTACTORFORRECT_HPP


#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/primitive/PLAPRMStroke.hpp"

class PLAOBJActor;

class PLAAGTActorForRect: public PLAAGTActor
{
public:
  explicit PLAAGTActorForRect(PLAOBJActor *aOwner);

  void SetFillColor(const PLAColor &aColor);
  void SetStroke(const PLAStroke &aStroke);
  void SetStrokeColor(const PLAColor &aColor);
  void SetStrokeWidth(PLAFloat aWidth);
  void SetStrokeJoin(PLAStrokeJoinType aJoin);
  void SetStrokeAlign(PLAStrokeAlignType aAlign);
};


#endif //ANHR_PLAAGTACTORFORRECT_HPP
