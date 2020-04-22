#include "PLAActor.hpp"
#include "PLAActorType.hpp"

PLAActor::PLAActor(PLAActorType aType,
                   const PLAVec3 &aPivot) :
_type(aType),
_actors(),
_pivot(aPivot)
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

void PLAActor::GetOrigin(PLAVec3 *aOrigin)
{
  PLAVec3 size(0);
  this->GetSize(&size);
  aOrigin->x = size.x * _pivot.x;
  aOrigin->y = size.y * _pivot.y;
  aOrigin->z = size.z * _pivot.z;
}
