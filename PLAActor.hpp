#ifndef PLAIN_PLAACTOR_HPP
#define PLAIN_PLAACTOR_HPP

#include <list>
#include "PLAObj.hpp"
#include "PLAShape.hpp"

class PLARenderer;

class PLAActor : public PLAObj
{
  std::list<PLAActor *> _actors = {};
  PLAVec3 _pivot = kPLAVec3None;
  PLAColor _color = kPLAColorWhite;
  PLATransform _transform = PLATransform();
  PLAShape *_shape = nullptr;

public :
  PLAActor(const PLAVec3 &aPivot,
           const PLAColor &aColor,
           const PLATransform &aTransform,
           const PLAShape &aShape);
  virtual ~PLAActor();

  void AddActor(PLAActor *aActor);

  void Update();
  void Render(const PLARenderer *aRenderer);

  const PLAVec3 &GetPivot() { return _pivot; };
  const PLATransform &GetTransform() { return _transform; };
  void GetOrigin(PLAVec3 *aOrigin);
  PLAVec3 GetSize() { return _shape->GetSize(); };
  void GetSize(PLAVec3 *aSize) { return _shape->GetSize(aSize); };

  size_t GetNumberOfActors() { return _actors.size(); };

  void SetPivot(const PLAVec3 &aPivot) { _pivot = aPivot; };
  void SetTransform(const PLATransform &aTransform)
  { _transform = aTransform; };
  virtual void SetSize(const PLAVec3 &aSize) { _shape->SetSize(aSize); };

  void SetTranslation(const PLAVec3 &aTranslation)
  { _transform.translation = aTranslation; };
  void SetRotation(const PLAVec3 &aRotation)
  { _transform.rotation = aRotation; };
  void SetScale(const PLAVec3 &aScale)
  { _transform.scale = aScale; };

protected :
  void OnUpdate();
  void OnRender(const PLARenderer *aRenderer);
};

#endif // PLAIN_PLAACTOR_HPP
