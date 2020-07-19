#ifndef PLAIN_PLAACTOR_HPP
#define PLAIN_PLAACTOR_HPP

#include <list>
#include <functional>
#include "Plain.hpp"
#include "PLAObject.hpp"
#include "PLAShape.hpp"

class PLARenderer;

class PLAActor : public PLAObject
{
  std::list<PLAActor *> _actors = {};
  PLAVec3 _pivot = kPLAVec3None;
  PLAColor _color = kPLAColorWhite;
  PLATransform _transform = PLATransform();
  PLAShape *_shape = nullptr;
  std::function<void(PLAActor *)> _fUpdate = [](PLAActor *aActor){};

  PLAVec3 _origin = kPLAVec3None;
  /// Calculate from pivot. Must be updated when pivot changes.

public :
  static PLAActor *Create(const PLAVec3 &aPivot,
                          const PLAColor &aColor,
                          const PLATransform &aTransform,
                          const PLAShape &aShape);

  PLAActor(const PLAVec3 &aPivot,
           const PLAColor &aColor,
           const PLATransform &aTransform,
           const PLAShape &aShape);
  virtual ~PLAActor();

  void AddActor(PLAActor *aActor);
  void Update();
  void PrintActors() const;

  const std::list<PLAActor *> *GetActors() const { return &_actors; };
  const PLAVec3 &GetPivot() const { return _pivot; };
  const PLAColor &GetColor() const { return _color; };
  const PLATransform &GetTransform() const { return _transform; };
  const PLAShape *GetShape() const { return _shape; }
  const PLAVec3 &GetOrigin() const { return _origin; };
  PLAVec3 GetSize() const { return _shape->GetSize(); };
  void GetSize(PLAVec3 *aSize) const { return _shape->GetSize(aSize); };

  PLAShapeType GetShapeType() const { return _shape->GetType(); }
  const PLAStyle *GetShapeStyle() const { return _shape->GetStyle(); }

  const PLASHPRect *GetShapeRect() const;
  const PLASHPCircle *GetShapeCircle() const;

  size_t GetNumberOfActors() { return _actors.size(); };

  void SetPivot(const PLAVec3 &aPivot)
  { _pivot = aPivot; this->RefreshOrigin(); };
  void SetTransform(const PLATransform &aTransform)
  { _transform = aTransform; };
  virtual void SetSize(const PLAVec3 &aSize)
  { _shape->SetSize(aSize); this->RefreshOrigin(); };

  void SetTranslation(const PLAVec3 &aTranslation)
  { _transform.translation = aTranslation; };
  void SetRotation(const PLAVec3 &aRotation)
  { _transform.rotation = aRotation; };
  void SetScale(const PLAVec3 &aScale)
  { _transform.scale = aScale; };

  void SetFunctorForUpdate(const std::function<void(PLAActor *)> &aFunc)
  { _fUpdate = aFunc; };

private:
  void RefreshOrigin();
};

#endif // PLAIN_PLAACTOR_HPP
