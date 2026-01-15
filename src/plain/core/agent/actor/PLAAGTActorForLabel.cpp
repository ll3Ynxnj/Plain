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

void PLAAGTActorForLabel::SetRasterScale(PLAFloat aScale)
{
  this->RefActor()->RefLayerForLabel()->SetRasterScale(aScale);
}

void PLAAGTActorForLabel::SetTextColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForLabel()->SetTextColor(aColor);
}

void PLAAGTActorForLabel::SetFillColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForLabel()->SetFillColor(aColor);
}
