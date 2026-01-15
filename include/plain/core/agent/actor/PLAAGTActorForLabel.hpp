// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef ANHR_PLAAGTACTORFORLABEL_HPP
#define ANHR_PLAAGTACTORFORLABEL_HPP

#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/primitive/PLAPRMColor.hpp"
#include "plain/core/PLATextAlignment.hpp"

class PLAOBJActor;

class PLAAGTActorForLabel : public PLAAGTActor
{
public:
  explicit PLAAGTActorForLabel(PLAOBJActor *aOwner);

  void SetText(const PLAString &aText);
  void SetFontSize(PLAFloat aFontSize);
  void SetRasterScale(PLAFloat aScale);
  void SetTextColor(const PLAColor &aColor);
  void SetFillColor(const PLAColor &aColor);
  void SetAlignment(PLATextAlignment aAlignment);
  void SetAlignmentWidth(PLAFloat aWidth);
};

#endif // ANHR_PLAAGTACTORFORLABEL_HPP
