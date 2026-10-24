// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLAAGTACTORFORLABEL_HPP
#define PLAIN_PLAAGTACTORFORLABEL_HPP

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
  void SetTextColor(const PLAColor &aColor);
  void SetFillColor(const PLAColor &aColor);
  void SetAlignment(PLATextAlignment aAlignment);
  void SetAlignmentWidth(PLAFloat aWidth);
  void SetAlignmentHeight(PLAFloat aHeight);
  void SetFontRasterizerByName(const PLAString &aRasterizerName);
};

#endif // PLAIN_PLAAGTACTORFORLABEL_HPP
