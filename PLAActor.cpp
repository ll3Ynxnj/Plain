#include "PLAActor.hpp"
#include "PLAActorType.hpp"

PLAActor::PLAActor(PLAActorType aType,
                   const PLAVec3 &aPivot,
                   const PLAVec3 &aPos,
                   const PLAVec3 &aSize) :
  _type(aType),
  _actors(),
  _pivot(aPivot),
  _origin(aSize.x * aPivot.x, aSize.y * aPivot.y, 0.0),
  _pos(aPos),
  _size(aSize)
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

void PLAActor::SetPivot(const PLAVec3 &aPivot)
{
  _pivot = aPivot;
  this->RefreshOrigin();
}

void PLAActor::SetSize(const PLAVec3 &aSize)
{
  _size = aSize;
  this->RefreshOrigin();
}

void PLAActor::RefreshOrigin()
{
  _origin.x = _size.x * _pivot.x;
  _origin.y = _size.y * _pivot.y;
  _origin.z = _size.z * _pivot.z;
}
