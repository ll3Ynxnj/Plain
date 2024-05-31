// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2022/04/28.
//

#include "plain/core/agent/actor/PLAAGTActor.hpp"
#include "plain/core/agent/PLAAGTMotion.hpp"

#include "plain/core/object/actor/PLAOBJActor.hpp"

PLAAGTActor::PLAAGTActor(PLAOBJActor *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTActor::~PLAAGTActor() noexcept
{

}

void PLAAGTActor::AddActor(PLAAGTActor aActor) const
{
  auto parentOwner = this->RefActor();
  auto childOwner = aActor.RefActor();
  parentOwner->AddActor(childOwner);
}

void PLAAGTActor::RemoveActor(PLAAGTActor aActor) const
{
  auto parentOwner = this->RefActor();
  auto childOwner = aActor.RefActor();
  parentOwner->RemoveActor(childOwner);
}

void PLAAGTActor::RemoveFromParentActor() const
{
  auto owner = this->RefActor();
  owner->RemoveFromParentActor();
}

const PLAVec3f &PLAAGTActor::GetPivot() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetPivot();
}

const PLAColor &PLAAGTActor::GetColor() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetColor();
}

PLAVec3f PLAAGTActor::GetSize() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetSize();
}

void PLAAGTActor::GetSize(PLAVec3f *aSize) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->GetSize(aSize);
}

const PLATransform &PLAAGTActor::GetTransform() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetTransform();
}

const PLAVec3f &PLAAGTActor::GetTranslation() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetTranslation();
}

const PLAVec3f &PLAAGTActor::GetRotation() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetRotation();
}

const PLAVec3f &PLAAGTActor::GetScale() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->GetScale();
}

void PLAAGTActor::SetPivot(const PLAVec3f &aPivot) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetPivot(aPivot);
}

void PLAAGTActor::SetColor(const PLAColor &aColor) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetColor(aColor);
}

void PLAAGTActor::SetTransform(const PLATransform &aTransform) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetTransform(aTransform);
};

void PLAAGTActor::SetSize(const PLAVec3f &aSize) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetSize(aSize);
};

void PLAAGTActor::SetTranslation(const PLAVec3f &aTranslation) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetTranslation(aTranslation);
};

void PLAAGTActor::SetRotation(const PLAVec3f &aRotation) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetRotation(aRotation);
};

void PLAAGTActor::SetScale(const PLAVec3f &aScale) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetScale(aScale);
};

void PLAAGTActor::SetImageClip(const PLAAGTImageClip &aImageClip) const
{
  PLAOBJImageClip *imageClip = aImageClip.RefImageClip();
  PLAOBJActor *actor = this->RefActor();
  actor->SetImageClip(imageClip);
}

void PLAAGTActor::SetFunction(PLAFunctionCode::Actor aKey,
                              const std::function<void(PLAOBJActor *)> &aFunc) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetFunction(aKey, aFunc);
};

PLABool PLAAGTActor::IsVisible() const
{
  PLAOBJActor *actor = this->RefActor();
  return actor->IsVisible();
}

void PLAAGTActor::SetVisible(PLABool aVisible) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetVisible(aVisible);
}

PLAId PLAAGTActor::GetActorTag() const
{
  auto actor = this->GetActor();
  return actor->GetActorTag();
}

void PLAAGTActor::SetActorTag(PLAId aActorTag) const
{
  auto actor = this->RefActor();
  actor->SetActorTag(aActorTag);
}

void PLAAGTActor::AddMotion(const PLAAGTMotion &aMotion) const
{
  auto id = aMotion.GetObjectId();
  auto motion = PLATMLMotion::Object(id);
  auto actor = this->RefActor();
  actor->AddTimelineThread(motion);
}

/*
void PLAAGTActor::AddTileMotion(const PLATileDataAddress &aAddress, const PLAAGTMotion &aMotion) const
{
  auto id = aMotion.GetObjectId();
  auto motion = PLATMLMotion::Object(id);
  auto actor = this->RefActor();
  actor->AddTileMotion(aAddress, motion);
}
 */

void PLAAGTActor::SetInputActive(bool aActive) const
{
  auto actor = this->RefActor();
  actor->SetInputActive(aActive);
}

void PLAAGTActor::SetFunctorForInputWithTouch
  (PLAInputSignalCodeForTouch aSignalCode,
   PLAInputActionCodeForTouch aActionCode,
   const std::function<void(const PLAAGTActor &, const PLAInput &)> &aFunc) const
{
  this->RefActor()->SetFunctorForInputWithTouch
  (aSignalCode, aActionCode,
   [aFunc](PLAInputContext *aContext, const PLAInput &aInput)
   {
    PLAOBJActor *actor = static_cast<PLAOBJActor *>(aContext);
    PLAAGTActor agent = actor->AssignAgent();
    aFunc(agent, aInput);
   });
}

void PLAAGTActor::SetFunctorForInputWithMouse
  (PLAInputSignalCodeForMouse aSignalCode,
   PLAInputActionCodeForMouse aActionCode,
   const std::function<void(const PLAAGTActor &, const PLAInput &)> &aFunc) const
{
  this->RefActor()->SetFunctorForInputWithMouse
    (aSignalCode, aActionCode,
     [aFunc](PLAInputContext *aContext, const PLAInput &aInput)
     {
       PLAOBJActor *actor = static_cast<PLAOBJActor *>(aContext);
       PLAAGTActor agent = actor->AssignAgent();
       aFunc(agent, aInput);
     });
}

void PLAAGTActor::SetFunctorForInputWithKeyboard
  (PLAInputSignalCodeForKeyboard aSignalCode,
   PLAInputActionCodeForKeyboard aActionCode,
   const std::function<void(const PLAAGTActor &, const PLAInput &)> &aFunc) const
{
  this->RefActor()->SetFunctorForInputWithKeyboard
    (aSignalCode, aActionCode,
     [aFunc](PLAInputContext *aContext, const PLAInput &aInput)
     {
       PLAOBJActor *actor = static_cast<PLAOBJActor *>(aContext);
       PLAAGTActor agent = actor->AssignAgent();
       aFunc(agent, aInput);
     });
}

const PLAOBJActor *PLAAGTActor::GetActor() const
{
  return static_cast<const PLAOBJActor *>(this->GetOwner());
}

PLAOBJActor *PLAAGTActor::RefActor() const
{
  return static_cast<PLAOBJActor *>(this->RefOwner());
}
