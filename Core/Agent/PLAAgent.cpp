//
// Created by Kentaro Kawai on 2022/04/16.
//

#include "PLAAgent.hpp"
#include "../Class/PLAObject.hpp"

PLAAgent::PLAAgent(PLAObject *aObject) :
  PLAObject(PLAObjectType::Agent),
  _object(aObject)
{

}

PLAAgent::~PLAAgent()
{

}

