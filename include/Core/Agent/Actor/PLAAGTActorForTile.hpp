// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#ifndef ANHR_PLAAGTACTORFORTILE_HPP
#define ANHR_PLAAGTACTORFORTILE_HPP


#include "Core/Agent/Actor/PLAAGTActor.hpp"
#include "Core/Object/Layer/IPLATileLayerDataSource.hpp"

class PLAOBJActor;

class PLAAGTActorForTile: public PLAAGTActor
{
public:
  explicit PLAAGTActorForTile(PLAOBJActor *aOwner);

  PLAVec2s GetTileSize() const;
  void SetTileSize(PLAVec2s aTileSize) const;
  void SetDataSource(IPLATileLayerDataSource *aDataSource) const;
};


#endif //ANHR_PLAAGTACTORFORTILE_HPP
