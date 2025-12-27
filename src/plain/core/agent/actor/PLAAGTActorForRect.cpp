// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#include "plain/core/agent/actor/PLAAGTActorForRect.hpp"
#include "plain/core/object/actor/PLAOBJActor.hpp"
#include "plain/core/object/layer/PLALYRRect.hpp"

PLAAGTActorForRect::PLAAGTActorForRect(PLAOBJActor *aOwner):
  PLAAGTActor(aOwner)
{

}

void PLAAGTActorForRect::SetFillColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForRect()->SetFillColor(aColor);
}

void PLAAGTActorForRect::SetStrokeColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForRect()->SetStrokeColor(aColor);
}

void PLAAGTActorForRect::SetStrokeWidth(PLAFloat aWidth)
{
  this->RefActor()->RefLayerForRect()->SetStrokeWidth(aWidth);
}

void PLAAGTActorForRect::SetStroke(const PLAStroke &aStroke)
{
  this->RefActor()->RefLayerForRect()->SetStroke(aStroke);
}

void PLAAGTActorForRect::SetStrokeJoin(PLAStrokeJoinType aJoin)
{
  this->RefActor()->RefLayerForRect()->SetStrokeJoin(aJoin);
}

void PLAAGTActorForRect::SetStrokeAlign(PLAStrokeAlignType aAlign)
{
  this->RefActor()->RefLayerForRect()->SetStrokeAlign(aAlign);
}
