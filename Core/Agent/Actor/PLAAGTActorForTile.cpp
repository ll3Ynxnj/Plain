// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#include "PLAAGTActorForTile.hpp"
#include "Object/Actor/PLAOBJActor.hpp"
#include "Object/Layer/PLALYRTile.hpp"

PLAAGTActorForTile::PLAAGTActorForTile(PLAOBJActor *aOwner):
PLAAGTActor(aOwner)
{

}

PLAVec2s PLAAGTActorForTile::GetTileSize() const
{
  auto owner = this->RefActor();
  auto layer = owner->RefLayerForTile();
  return layer->GetTileSize();
}

void PLAAGTActorForTile::SetTileSize(PLAVec2s aTileSize) const
{
  auto owner = this->RefActor();
  auto layer = owner->RefLayerForTile();
  layer->SetTileSize(aTileSize);
}

void PLAAGTActorForTile::SetDataSource(IPLATileLayerDataSource *aDataSource) const
{
  auto owner = this->RefActor();
  auto layer = owner->RefLayerForTile();
  layer->SetDataSource(aDataSource);
}
