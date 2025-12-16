// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_PLAAGTACTORFORPOINT_HPP
#define PLAIN_PLAAGTACTORFORPOINT_HPP

#include "plain/core/agent/actor/PLAAGTActor.hpp"

class PLAOBJActor;

class PLAAGTActorForPoint: public PLAAGTActor
{
public:
  explicit PLAAGTActorForPoint(PLAOBJActor *aOwner);
};

#endif //PLAIN_PLAAGTACTORFORPOINT_HPP
