//
// Created by Kentaro Kawai on 2022/04/28.
//

#include "PLAAGTActor.hpp"

PLAAGTActor *PLAAGTActor::Create(PLAActor *aActor)
{
  auto agent = new PLAAGTActor(aActor);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTActor::PLAAGTActor(PLAActor *aActor) :
  PLAAgent(aActor)
{

}

PLAAGTActor::~PLAAGTActor() noexcept
{

}

void PLAAGTActor::SetColor(const PLAColor &aColor) const
{
  PLAActor *actor = this->RefActor();
  actor->SetColor(aColor);
}

void PLAAGTActor::SetTransform(const PLATransform &aTransform) const
{
  PLAActor *actor = this->RefActor();
  actor->SetTransform(aTransform);
};

void PLAAGTActor::SetSize(const PLAVec3 &aSize) const
{
  PLAActor *actor = this->RefActor();
  actor->SetSize(aSize);
};

void PLAAGTActor::SetTranslation(const PLAVec3 &aTranslation) const
{
  PLAActor *actor = this->RefActor();
  actor->SetTranslation(aTranslation);
};

void PLAAGTActor::SetRotation(const PLAVec3 &aRotation) const
{
  PLAActor *actor = this->RefActor();
  actor->SetRotation(aRotation);
};

void PLAAGTActor::SetScale(const PLAVec3 &aScale) const
{
  PLAActor *actor = this->RefActor();
  actor->SetScale(aScale);
};

void PLAAGTActor::SetFunction(PLAActorFunctionCode aKey,
                              const std::function<void(PLAActor *)> &aFunc) const
{
  PLAActor *actor = this->RefActor();
  actor->SetFunction(aKey, aFunc);
};

void PLAAGTActor::AddTileMotion(const PLAVec2s &aAddress, PLAMotion *aThread) const
{
  PLAActor *actor = this->RefActor();
  actor->AddTileMotion(aAddress, aThread);
}
