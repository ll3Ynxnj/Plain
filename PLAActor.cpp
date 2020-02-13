#include "PLAActor.hpp"

PLAActor::PLAActor(PLAActorType aType) :
  _type(aType),
  _actors()
{

}

PLAActor::~PLAActor()
{

}

void PLAActor::AddActor(PLAActor *aActor)
{
  _actors.push_back(aActor);
}

void PLAActor::Update()
{
  for (PLAActor *actor : _actors)
  {
    actor->OnUpdate();
  }
}

void PLAActor::Render()
{
  for (PLAActor *actor : _actors)
  {
    actor->OnRender();
  }
}
