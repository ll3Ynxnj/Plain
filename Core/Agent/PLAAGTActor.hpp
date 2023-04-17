//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTACTOR_HPP
#define ANHR_PLAAGTACTOR_HPP


#include "PLAAgent.hpp"
#include "Object/Actor/PLAOBJActor.hpp"

class PLAAGTActor final : public PLAAgent//, public PLAInputContext
{
public:
  /// Agent is const method only.
  //static PLAAGTActor *Create(PLAOBJActor *aActor);

  explicit PLAAGTActor(PLAOBJActor *aActor);
  virtual ~PLAAGTActor() noexcept;

  void SetColor(const PLAColor &aColor) const;
  void SetTransform(const PLATransform &aTransform) const;
  void SetSize(const PLAVec3f &aSize) const;

  void SetTranslation(const PLAVec3f &aTranslation) const;
  void SetRotation(const PLAVec3f &aRotation) const;
  void SetScale(const PLAVec3f &aScale) const;

  void SetFunction(PLAOBJActorFunctionCode aKey,
                   const std::function<void(PLAOBJActor *)> &aFunc) const;

  void AddTileMotion(const PLAVec2s &aAddress, PLATMLMotion *aThread) const;

  /// Path-through to InputContext /////////////////////////////////////////////
  void SetFunctorForInputWithTouch
    (PLAInputSignalCodeForTouch aSignalCode,
     PLAInputActionCodeForTouch aActionCode,
     const std::function<void(const PLAAGTActor &, const PLAInput &)> &aFunc) const;
  void SetFunctorForInputWithMouse
    (PLAInputSignalCodeForMouse aSignalCode,
     PLAInputActionCodeForMouse aActionCode,
     const std::function<void(const PLAAGTActor &, const PLAInput &)> &aFunc) const;
  void SetFunctorForInputWithKeyboard
    (PLAInputSignalCodeForKeyboard aSignalCode,
     PLAInputActionCodeForKeyboard aActionCode,
     const std::function<void(const PLAAGTActor &, const PLAInput &)> &aFunc) const;


protected:
  const PLAOBJActor *GetActor() const
  { return static_cast<const PLAOBJActor *>(this->GetOwner()); }
  PLAOBJActor *RefActor() const
  { return static_cast<PLAOBJActor *>(this->RefOwner()); }
};


#endif //ANHR_PLAAGTACTOR_HPP
