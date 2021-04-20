#ifndef PLAIN_ENGINE_PLAACTOR_HPP
#define PLAIN_ENGINE_PLAACTOR_HPP

#include <list>
#include <functional>
//#include "PLAType.hpp"
#include "PLAObject.hpp"
#include "PLAScene.hpp"
#include "PLAInput.hpp"
#include "PLALayer.hpp"
#include "Grain/GRAFunctor.hpp"
#include "PLACollision.hpp"

class PLARenderer;

class PLAActor : public PLAObject, public PLAInputContext,
  public GRAListener<PLAScene, PLAScene::FunctionCode>
{
public:
  enum class FunctionCode : PLACode
  {
    OnInit,
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
    Layer,

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
  PLALayer *_layer = nullptr;
  //PLAStyle _style = PLAStyle();
  CollisionItem collisions[static_cast<unsigned>(CollisionCode::kNumberOfItems)];

  GRAFunctor<PLAActor, FunctionCode> _functor = GRAFunctor<PLAActor, FunctionCode>();

  /// Calculate from pivot. Must be updated when pivot changes.

public :
  static PLAActor *Create(const PLAVec3 &aPivot,
                          const PLAColor &aColor,
                          const PLATransform &aTransform,
                          const PLALayer &aLayer);

  PLAActor(const PLAVec3 &aPivot,
           const PLAColor &aColor,
           const PLATransform &aTransform,
           const PLALayer &aLayer);
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
  { _pivot = aPivot; this->RefreshLayerOffset(); };
  const PLAColor &GetColor() const { return _color; };
  const PLATransform &GetTransform() const { return _transform; };
  const PLALayer *GetLayer() const { return _layer; }
  PLAVec3 GetSize() const { return _layer->GetSize(); };
  void GetSize(PLAVec3 *aSize) const { return _layer->GetSize(aSize); };
  const PLAVec3 &GetLayerOffset() const { return _layer->GetOffset(); };

  PLALayerType GetLayerType() const { return _layer->GetLayerType(); }
  //const PLAStyle *GetLayerStyle() const { return _layer->GetStyle(); }

  //const PLAStyle *GetStyle() const { return &_style; };
  //void SetStyle(const PLAStyle &aStyle) { _style = aStyle; }

  /*
  const PLALYRRect *GetLayerRect() const;
  const PLALYRCircle *GetLayerCircle() const;
  */

  size_t GetNumberOfActors() { return _actors.size(); };

  PLAActor *RefActorWithPoint(const PLAPoint &aPoint);
  //PLAActor *RefActorWithInput(const PLAInput &aInput);

  void SetColor(const PLAColor &aColor)
  { _color = aColor; };
  void SetTransform(const PLATransform &aTransform)
  { _transform = aTransform; };
  virtual void SetSize(const PLAVec3 &aSize)
  { _layer->SetSize(aSize, _pivot); this->RefreshLayerOffset(); };

  void SetTranslation(const PLAVec3 &aTranslation)
  { _transform.translation = aTranslation; };
  void SetRotation(const PLAVec3 &aRotation)
  { _transform.rotation = aRotation; };
  void SetScale(const PLAVec3 &aScale)
  { _transform.scale = aScale; };

  void SetFunction(FunctionCode aKey,
                   const std::function<void(PLAActor *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

private:
  void RefreshLayerOffset();
};

#endif // PLAIN_ENGINE_PLAACTOR_HPP
