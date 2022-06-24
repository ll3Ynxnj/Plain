//
// Created by Kentaro Kawai on 2022/04/28.
//

#include "PLAAGTActor.hpp"

PLAAGTActor *PLAAGTActor::Create(PLAOBJActor *aActor)
{
  auto agent = new PLAAGTActor(aActor);
  agent->PLAObject::Bind();
  return agent;
}

PLAAGTActor::PLAAGTActor(PLAOBJActor *aActor) :
  PLAOBJAgent(aActor)
{

}

PLAAGTActor::~PLAAGTActor() noexcept
{

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

void PLAAGTActor::SetSize(const PLAVec3 &aSize) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetSize(aSize);
};

void PLAAGTActor::SetTranslation(const PLAVec3 &aTranslation) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetTranslation(aTranslation);
};

void PLAAGTActor::SetRotation(const PLAVec3 &aRotation) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetRotation(aRotation);
};

void PLAAGTActor::SetScale(const PLAVec3 &aScale) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetScale(aScale);
};

void PLAAGTActor::SetFunction(PLAOBJActorFunctionCode aKey,
                              const std::function<void(PLAOBJActor *)> &aFunc) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->SetFunction(aKey, aFunc);
};

void PLAAGTActor::AddTileMotion(const PLAVec2s &aAddress, PLATMLMotion *aThread) const
{
  PLAOBJActor *actor = this->RefActor();
  actor->AddTileMotion(aAddress, aThread);
}

void PLAAGTActor::SetFunctorForInputWithTouch
  (PLAInputSignalCodeForTouch aSignalCode,
   PLAInputActionCodeForTouch aActionCode,
   const std::function<void(PLAAGTActor *, const PLAInput &)> &aFunc)
{
  this->RefActor()->SetFunctorForInputWithTouch
  (aSignalCode, aActionCode,
   [aFunc](PLAInputContext *aContext, const PLAInput &aInput)
   {
    PLAOBJActor *actor = static_cast<PLAOBJActor *>(aContext);
    PLAAGTActor *agent = static_cast<PLAAGTActor *>(actor->AssignAgent());
    aFunc(agent, aInput);
    agent->Release();
   });
}

void PLAAGTActor::SetFunctorForInputWithMouse
  (PLAInputSignalCodeForMouse aSignalCode,
   PLAInputActionCodeForMouse aActionCode,
   const std::function<void(PLAAGTActor *, const PLAInput &)> &aFunc)
{
  this->RefActor()->SetFunctorForInputWithMouse
    (aSignalCode, aActionCode,
     [aFunc](PLAInputContext *aContext, const PLAInput &aInput)
     {
       PLAOBJActor *actor = static_cast<PLAOBJActor *>(aContext);
       PLAAGTActor *agent = static_cast<PLAAGTActor *>(actor->AssignAgent());
       aFunc(agent, aInput);
       agent->Release();
     });
}

void PLAAGTActor::SetFunctorForInputWithKeyboard
  (PLAInputSignalCodeForKeyboard aSignalCode,
   PLAInputActionCodeForKeyboard aActionCode,
   const std::function<void(PLAAGTActor *, const PLAInput &)> &aFunc)
{
  this->RefActor()->SetFunctorForInputWithKeyboard
    (aSignalCode, aActionCode,
     [aFunc](PLAInputContext *aContext, const PLAInput &aInput)
     {
       PLAOBJActor *actor = static_cast<PLAOBJActor *>(aContext);
       PLAAGTActor *agent = static_cast<PLAAGTActor *>(actor->AssignAgent());
       aFunc(agent, aInput);
       agent->Release();
     });
}
