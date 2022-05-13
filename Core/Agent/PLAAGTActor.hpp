//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTACTOR_HPP
#define ANHR_PLAAGTACTOR_HPP


#include "PLAAgent.hpp"
#include "Actor/PLAActor.hpp"

class PLAAGTActor final : public PLAAgent//, public PLAInputContext
{
public:
  /// Agent is const method only.
  static PLAAGTActor *Create(PLAActor *aActor);

  virtual ~PLAAGTActor();

  void SetColor(const PLAColor &aColor) const;
  void SetTransform(const PLATransform &aTransform) const;
  void SetSize(const PLAVec3 &aSize) const;

  void SetTranslation(const PLAVec3 &aTranslation) const;
  void SetRotation(const PLAVec3 &aRotation) const;
  void SetScale(const PLAVec3 &aScale) const;

  void SetFunction(PLAActorFunctionCode aKey,
                   const std::function<void(PLAActor *)> &aFunc) const;

  void AddTileMotion(const PLAVec2s &aAddress, PLAMotion *aThread) const;

  /// Path-through to InputContext /////////////////////////////////////////////
  void SetFunctorForInputWithTouch
    (PLAInputSignalCodeForTouch aSignalCode,
     PLAInputActionCodeForTouch aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  {
    this->RefActor()->SetFunctorForInputWithTouch(aSignalCode,
                                                  aActionCode,
                                                  aFunc);
  }

  void SetFunctorForInputWithMouse
    (PLAInputSignalCodeForMouse aSignalCode,
     PLAInputActionCodeForMouse aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  {
    this->RefActor()->SetFunctorForInputWithMouse(aSignalCode,
                                                  aActionCode,
                                                  aFunc);
  }

  void SetFunctorForInputWithKeyboard
    (PLAInputSignalCodeForKeyboard aSignalCode,
     PLAInputActionCodeForKeyboard aActionCode,
     const std::function<void(PLAInputContext *, const PLAInput &)> &aFunc)
  {
    this->RefActor()->SetFunctorForInputWithKeyboard(aSignalCode,
                                                     aActionCode,
                                                     aFunc);
  }


protected:
  PLAAGTActor(PLAActor *aActor);
  const PLAActor *GetActor() const
  { return static_cast<const PLAActor *>(this->GetOwner()); }
  PLAActor *RefActor() const
  { return static_cast<PLAActor *>(this->RefOwner()); }
};


#endif //ANHR_PLAAGTACTOR_HPP
