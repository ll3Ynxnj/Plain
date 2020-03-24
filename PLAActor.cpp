#include "PLAActor.hpp"
#include "PLAActorType.hpp"

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
  this->OnUpdate();
  for (PLAActor *actor : _actors)
  {
    actor->Update();
  }
}

void PLAActor::Render()
{
  this->OnRender();
  for (PLAActor *actor : _actors)
  {
    actor->Render();
  }
}

size_t PLAActor::GetSizeOfActors()
{
  return _actors.size();
}
