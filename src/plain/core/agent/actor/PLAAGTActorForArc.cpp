// Copyright (c) 2024. CLAYWORK Inc. All rights reserved.

#include "plain/core/agent/actor/PLAAGTActorForArc.hpp"
#include "plain/core/object/actor/PLAOBJActor.hpp"
#include "plain/core/object/layer/PLALYRArc.hpp"

PLAAGTActorForArc::PLAAGTActorForArc(PLAOBJActor *aOwner):
  PLAAGTActor(aOwner)
{

}

PLAFloat PLAAGTActorForArc::GetStartAngle() const
{
  return this->RefActor()->RefLayerForArc()->GetStartAngle();
}

PLAFloat PLAAGTActorForArc::GetEndAngle() const
{
  return this->RefActor()->RefLayerForArc()->GetEndAngle();
}

PLAFloat PLAAGTActorForArc::GetAngleSpan() const
{
  return this->RefActor()->RefLayerForArc()->GetAngleSpan();
}

void PLAAGTActorForArc::SetStartAngle(PLAFloat aAngle)
{
  this->RefActor()->RefLayerForArc()->SetStartAngle(aAngle);
}

void PLAAGTActorForArc::SetEndAngle(PLAFloat aAngle)
{
  this->RefActor()->RefLayerForArc()->SetEndAngle(aAngle);
}

void PLAAGTActorForArc::SetAngles(PLAFloat aStartAngle, PLAFloat aEndAngle)
{
  this->RefActor()->RefLayerForArc()->SetAngles(aStartAngle, aEndAngle);
}

void PLAAGTActorForArc::SetFillColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForArc()->SetFillColor(aColor);
}

void PLAAGTActorForArc::SetStrokeColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForArc()->SetStrokeColor(aColor);
}

void PLAAGTActorForArc::SetStrokeWidth(PLAFloat aWidth)
{
  this->RefActor()->RefLayerForArc()->SetStrokeWidth(aWidth);
}

void PLAAGTActorForArc::SetStroke(const PLAStroke &aStroke)
{
  this->RefActor()->RefLayerForArc()->SetStroke(aStroke);
}

void PLAAGTActorForArc::SetStrokeJoin(PLAStroke::Join aJoin)
{
  this->RefActor()->RefLayerForArc()->SetStrokeJoin(aJoin);
}

void PLAAGTActorForArc::SetStrokeAlign(PLAStroke::Align aAlign)
{
  this->RefActor()->RefLayerForArc()->SetStrokeAlign(aAlign);
}
