// Copyright (c) 2024. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLAAGTACTORFORARC_HPP
#define PLAIN_PLAAGTACTORFORARC_HPP

#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"

class PLAOBJActor;

class PLAAGTActorForArc : public PLAAGTActor
{
public:
  explicit PLAAGTActorForArc(PLAOBJActor *aOwner);

  PLAFloat GetStartAngle() const;
  PLAFloat GetEndAngle() const;
  PLAFloat GetAngleSpan() const;

  void SetStartAngle(PLAFloat aAngle);
  void SetEndAngle(PLAFloat aAngle);
  void SetAngles(PLAFloat aStartAngle, PLAFloat aEndAngle);

  void SetFillColor(const PLAColor &aColor);
  void SetStrokeColor(const PLAColor &aColor);
  void SetStrokeWidth(PLAFloat aWidth);
};

#endif //PLAIN_PLAAGTACTORFORARC_HPP
