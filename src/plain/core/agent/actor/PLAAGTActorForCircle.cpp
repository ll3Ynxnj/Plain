// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#include "plain/core/agent/actor/PLAAGTActorForCircle.hpp"
#include "plain/core/object/actor/PLAOBJActor.hpp"
#include "plain/core/object/layer/PLALYRCircle.hpp"

PLAAGTActorForCircle::PLAAGTActorForCircle(PLAOBJActor *aOwner):
  PLAAGTActor(aOwner)
{

}

PLAFloat PLAAGTActorForCircle::GetRadius() const
{
  return this->RefActor()->RefLayerForCircle()->GetRadius();
}

void PLAAGTActorForCircle::SetRadius(PLAFloat aRadius)
{
  this->RefActor()->RefLayerForCircle()->SetRadius(aRadius);
}

void PLAAGTActorForCircle::SetStrokeColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForCircle()->SetStrokeColor(aColor);
}

void PLAAGTActorForCircle::SetStrokeWidth(PLAFloat aWidth)
{
  this->RefActor()->RefLayerForCircle()->SetStrokeWidth(aWidth);
}

void PLAAGTActorForCircle::SetStroke(const PLAStroke &aStroke)
{
  this->RefActor()->RefLayerForCircle()->SetStroke(aStroke);
}

void PLAAGTActorForCircle::SetStrokeJoin(PLAStroke::Join aJoin)
{
  this->RefActor()->RefLayerForCircle()->SetStrokeJoin(aJoin);
}

void PLAAGTActorForCircle::SetStrokeAlign(PLAStroke::Align aAlign)
{
  this->RefActor()->RefLayerForCircle()->SetStrokeAlign(aAlign);
}
