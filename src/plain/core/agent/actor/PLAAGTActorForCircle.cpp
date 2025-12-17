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

void PLAAGTActorForCircle::SetStrokeColor(const PLAColor &aColor)
{
  this->RefActor()->RefLayerForCircle()->SetStrokeColor(aColor);
}
