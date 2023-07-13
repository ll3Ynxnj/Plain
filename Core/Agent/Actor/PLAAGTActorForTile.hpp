// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2023/07/13.
//

#ifndef ANHR_PLAAGTACTORFORTILE_HPP
#define ANHR_PLAAGTACTORFORTILE_HPP


#include "Agent/Actor/PLAAGTActor.hpp"
#include "Object/Layer/IPLATileLayerDataSource.hpp"

class PLAOBJActor;

class PLAAGTActorForTile: public PLAAGTActor
{
public:
  explicit PLAAGTActorForTile(PLAOBJActor *aOwner);

  void SetDataSource(IPLATileLayerDataSource *aDataSource) const;
};


#endif //ANHR_PLAAGTACTORFORTILE_HPP
