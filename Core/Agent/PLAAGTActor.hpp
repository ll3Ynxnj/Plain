//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTACTOR_HPP
#define ANHR_PLAAGTACTOR_HPP


#include "PLAAgent.hpp"
#include "PLAAGTMotion.hpp"
#include "PLAAGTImageClip.hpp"
#include "PLAFunctionCode.hpp"

#include "Primitive/PLAPRMColor.hpp"
#include "Primitive/PLAPRMTransform.hpp"

#include "Object/Input/PLAInput.hpp"

class PLAOBJActor;

class PLAAGTActor final : public PLAAgent
{
public:
  /// Agent is const method only.
  explicit PLAAGTActor(PLAOBJActor *aOwner);
  virtual ~PLAAGTActor() noexcept;

  void AddActor(PLAAGTActor aActor) const;
  void RemoveActor(PLAAGTActor aActor) const;
  void RemoveFromParentActor() const;

  void SetPivot(const PLAVec3f &aPivot) const;
  void SetColor(const PLAColor &aColor) const;
  void SetTransform(const PLATransform &aTransform) const;
  void SetSize(const PLAVec3f &aSize) const;

  void SetTranslation(const PLAVec3f &aTranslation) const;
  void SetRotation(const PLAVec3f &aRotation) const;
  void SetScale(const PLAVec3f &aScale) const;

  void SetImageClip(const PLAAGTImageClip &aImageClip) const;

  void SetFunction(PLAFunctionCode::Actor aKey,
                   const std::function<void(PLAOBJActor *)> &aFunc) const;

  void AddTileMotion(const PLAVec2s &aAddress, const PLAAGTMotion &aThread) const;

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


//protected:
  const PLAOBJActor *GetActor() const;
  PLAOBJActor *RefActor() const;
};


#endif //ANHR_PLAAGTACTOR_HPP
