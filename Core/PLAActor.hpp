#ifndef PLAIN_ENGINE_PLAACTOR_HPP
#define PLAIN_ENGINE_PLAACTOR_HPP

#include <list>
#include <functional>
//#include "PLAType.hpp"
#include "PLAObject.hpp"
#include "PLAScene.hpp"
#include "PLAInput.hpp"
#include "PLAShape.hpp"
#include "PLAFunctor.hpp"
#include "PLACollision.hpp"

class PLARenderer;

class PLAActor : public PLAObject, public PLAInputContext, public PLAScene::Delegate
{
public:
  enum class FunctionCode : PLACode
  {
    OnUpdate,
    OnAppear,
    OnDisappear,

    kNumberOfItems,
    None,
  };

  enum class CollisionCode : PLACode
  {
    Input,
    Actor,

    kNumberOfItems,
    None,
  };

  enum class CollisionSyncCode : PLACode
  {
    Size,
    Shape,

    kNumberOfItems,
    None,
  };

private:
  struct CollisionItem
  {
    PLACollision *collision = nullptr;
    bool syncMode[static_cast<unsigned>(CollisionSyncCode::kNumberOfItems)] =
    { false };
  };

  std::list<PLAActor *> _actors = {};
  PLAVec3 _pivot = kPLAVec3None;
  PLAColor _color = kPLAColorWhite;
  PLATransform _transform = PLATransform();
  //-- Not affect child actors
  PLAShape *_shape = nullptr;
  PLAStyle _style = PLAStyle();
  CollisionItem collisions[static_cast<unsigned>(CollisionCode::kNumberOfItems)];

  PLAFunctor<PLAActor> _functor = PLAFunctor<PLAActor>();
  /*
  std::function<void(PLAActor *)> _fOnInit = [](PLAActor *){};
  std::function<void(PLAActor *)> _fOnUpdate = [](PLAActor *){};
  std::function<void(PLAActor *)> _fOnAppear = [](PLAActor *){};
  std::function<void(PLAActor *)> _fOnDisappear = [](PLAActor *){};
   */

  //PLAVec3 _origin = kPLAVec3None;
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
  void Input(const PLAInput *aInput);

  void Init();
  void Update();
  void Appear();
  void Disappear();

  void PrintActors() const;

  //bool IsCollideWithInput(const PLAInput &aInput) const;
  bool IsCollideWithActor(const PLAActor *aActor) const;
  bool IsCollideWithPoint(PLAPoint aPoint) const;
  //bool IsCollideWithRect(PLARect aRect) const;

  const std::list<PLAActor *> *GetActors() const { return &_actors; };
  const PLAVec3 &GetPivot() const { return _pivot; };
  void SetPivot(const PLAVec3 &aPivot)
  { _pivot = aPivot; this->RefreshShapeOffset(); };
  const PLAColor &GetColor() const { return _color; };
  const PLATransform &GetTransform() const { return _transform; };
  const PLAShape *GetShape() const { return _shape; }
  PLAVec3 GetSize() const { return _shape->GetSize(); };
  void GetSize(PLAVec3 *aSize) const { return _shape->GetSize(aSize); };
  const PLAVec3 &GetShapeOffset() const { return _shape->GetOffset(); };

  PLAShapeType GetShapeType() const { return _shape->GetShapeType(); }
  //const PLAStyle *GetShapeStyle() const { return _shape->GetStyle(); }

  const PLAStyle *GetStyle() const { return &_style; };
  void SetStyle(const PLAStyle &aStyle) { _style = aStyle; }

  /*
  const PLASHPRect *GetShapeRect() const;
  const PLASHPCircle *GetShapeCircle() const;
  */

  size_t GetNumberOfActors() { return _actors.size(); };

  PLAActor *RefActorWithPoint(const PLAPoint &aPoint);
  //PLAActor *RefActorWithInput(const PLAInput &aInput);

  void SetColor(const PLAColor &aColor)
  { _color = aColor; };
  void SetTransform(const PLATransform &aTransform)
  { _transform = aTransform; };
  virtual void SetSize(const PLAVec3 &aSize)
  { _shape->SetSize(aSize, _pivot); this->RefreshShapeOffset(); };

  void SetTranslation(const PLAVec3 &aTranslation)
  { _transform.translation = aTranslation; };
  void SetRotation(const PLAVec3 &aRotation)
  { _transform.rotation = aRotation; };
  void SetScale(const PLAVec3 &aScale)
  { _transform.scale = aScale; };

  void SetFunction(const std::string &aKey,
                   const std::function<void(PLAActor *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };
  /*
  void SetFunctorOnInit(const std::function<void(PLAActor *)> &aFunc)
  //{ _fOnInit = aFunc; };
  { _functor.SetFunctorOnInit(aFunc); };
  void SetFunctorOnUpdate(const std::function<void(PLAActor *)> &aFunc)
  //{ _fOnUpdate = aFunc; };
  { _functor.SetFunctorOnUpdate(aFunc); };
  void SetFunctorOnAppear(const std::function<void(PLAActor *)> &aFunc)
  //{ _fOnAppear = aFunc; };
  { _functor.SetFunctorOnAppear(aFunc); };
  void SetFunctorOnDisappear(const std::function<void(PLAActor *)> &aFunc)
  //{ _fOnDisappear = aFunc; };
  { _functor.SetFunctorOnDisappear(aFunc); };
  */

private:
  void RefreshShapeOffset();
};

#endif // PLAIN_ENGINE_PLAACTOR_HPP
