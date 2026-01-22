// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/agent/actor/PLAAGTActorForLabel.hpp"
#include "plain/core/object/actor/PLAOBJActor.hpp"
#include "plain/core/object/layer/PLALYRLabel.hpp"

PLAAGTActorForLabel::PLAAGTActorForLabel(PLAOBJActor *aOwner) :
  PLAAGTActor(aOwner)
{
}

void PLAAGTActorForLabel::SetText(const PLAString &aText)
{
  this->RefActor()->RefLayerForLabel()->SetText(aText);
}

void PLAAGTActorForLabel::SetFontSize(PLAFloat aFontSize)
{
  this->RefActor()->RefLayerForLabel()->SetFontSize(aFontSize);
}

void PLAAGTActorForLabel::SetTextColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForLabel()->SetTextColor(aColor);
}

void PLAAGTActorForLabel::SetFillColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForLabel()->SetFillColor(aColor);
}

void PLAAGTActorForLabel::SetAlignment(PLATextAlignment aAlignment)
{
  this->RefActor()->RefLayerForLabel()->SetAlignment(aAlignment);
}

void PLAAGTActorForLabel::SetAlignmentWidth(PLAFloat aWidth)
{
  this->RefActor()->RefLayerForLabel()->SetAlignmentWidth(aWidth);
}

void PLAAGTActorForLabel::SetAlignmentHeight(PLAFloat aHeight)
{
  this->RefActor()->RefLayerForLabel()->SetAlignmentHeight(aHeight);
}

void PLAAGTActorForLabel::SetFontRasterizerByName(const PLAString &aRasterizerName)
{
  this->RefActor()->RefLayerForLabel()->SetFontRasterizerByName(aRasterizerName);
}
