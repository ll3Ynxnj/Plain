// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

//
// Created by Kentaro Kawai on 2022/04/28.
//

#ifndef ANHR_PLAAGTACTOR_HPP
#define ANHR_PLAAGTACTOR_HPP


#include "Core/Agent/PLAAgent.hpp"
#include "Core/Agent/PLAAGTMotion.hpp"
#include "Core/Agent/PLAAGTImageClip.hpp"
#include "PLAFunctionCode.hpp"

#include "Primitive/PLAPRMColor.hpp"
#include "Primitive/PLAPRMTransform.hpp"

#include "Object/Input/PLAInput.hpp"
#include "Object/Layer/PLALYRTile.hpp"

class PLAOBJActor;

class PLAAGTActor : public PLAAgent
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

  PLABool IsVisible() const;
  void SetVisible(bool aVisible) const;

  PLAId GetActorTag() const;
  void SetActorTag(PLAId aTag) const;

  void AddMotion(const PLAAGTMotion &aMotion) const;
  //void AddTileMotion(const PLATileDataAddress &aAddress, const PLAAGTMotion &aMotion) const;

  /// Path-through to InputContext /////////////////////////////////////////////
  void SetInputActive(bool aActive) const;
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
  const PLAOBJActor *GetActor() const;
  PLAOBJActor *RefActor() const;
};

#endif //ANHR_PLAAGTACTOR_HPP
