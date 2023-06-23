#ifndef PLAIN_ENGINE_PLAOBJACTOR_HPP
#define PLAIN_ENGINE_PLAOBJACTOR_HPP

#include <list>
#include <functional>

#include "Object/PLAObject.hpp"
#include "Object/Input/PLAInputContext.hpp"
//#include "Grain/Object/GRAOBJListener.hpp"
#include "Object/PLAOBJScene.hpp"
#include "Grain/Object/GRAOBJBinder.hpp"

#include "PLAFunctionCode.hpp"
#include "Core/Library/PLALIBCollision.hpp"
#include "PLAActorCollisionCode.hpp"
#include "PLAActorCollisyncCode.hpp"
#include "Primitive/PLAPRMColor.hpp"
#include "Primitive/PLAPRMVector.hpp"
#include "Primitive/PLAPRMTransform.hpp"
#include "Object/Layer/PLAOBJLayer.hpp"
#include "Object/Layer/IPLATileLayerDataSource.hpp"
#include "Object/Timeline/PLATimelineHolder.hpp"
#include "Object/Timeline/PLATMLMotionNode.hpp"
#include "Object/Timeline/PLATMLMotion.hpp"

#include "PLAFunctionCode.hpp"

class PLAOBJRenderer;
class PLAAGTActor;

class PLAOBJActor final :
  public PLAObject, public PLAInputContext, public PLATimelineHolder,
  //public GRAOBJListener<PLAOBJScene, PLAFunctionCode::Scene>,
  public PLAOBJPhase::Listener,
  public GRAOBJBinder<PLAOBJActor>::Item
{
public:
  static PLAOBJActor *Object(const PLAString &aName);
  static PLAOBJActor *Object(PLAId aId);

private:
  struct CollisionItem
  {
    PLACollision *collision = nullptr;
    bool syncMode[static_cast<unsigned>(PLAActorCollisyncCode::kNumberOfItems)] =
    { false };
  };

  PLAOBJActor * _parent = nullptr;
  std::list<PLAOBJActor *> _actors = {};
  PLAVec3f _pivot = kPLAVec3fNone;
  PLAColor _color = kPLAColorWhite;
  PLATransform _transform = kPLATransformNorm;
  PLAOBJLayer *_layer = nullptr;
  CollisionItem collisions[static_cast<unsigned>(PLAActorCollisionCode::kNumberOfItems)];

  GRAOBJFunctor<PLAOBJActor *, PLAFunctionCode::Actor> _functor = GRAOBJFunctor<PLAOBJActor *, PLAFunctionCode::Actor>();

  /// Calculate from pivot. Must be updated when pivot changes.

protected:
  PLAOBJActor(const PLAVec3f &aPivot,
              const PLAColor &aColor,
              const PLATransform &aTransform,
              PLAOBJLayer *aLayer);//,

public:
  static PLAOBJActor *CreateRect(const PLAVec3f &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLARect &aRect);

  static PLAOBJActor *CreateRect(const PLAVec3f &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLARect &aRect,
                                 const PLAColor &aFillColor);

  static PLAOBJActor *CreateRect(const PLAVec3f &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLARect &aRect,
                                 const std::string &aImage,
                                 const PLARect &aClip);

  static PLAOBJActor *CreateCircle(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLACircle &aCircle);

  static PLAOBJActor *CreateCircle(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLACircle &aCircle,
                                   const PLAColor &aFillColor);

  static PLAOBJActor *CreateCircle(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLACircle &aCircle,
                                   const std::string &aImage,
                                   const PLARect &aClip);

  static PLAOBJActor *CreateTile(const PLAVec2f &aOffset,
                                 const std::string &aImageName,
                                 const GRAVec2<PLASize> &aTileSize,
                                 const GRAVec2<PLASize> &aChipSize,
                                 const IPLATileLayerDataSource *aDataSource);

  virtual ~PLAOBJActor() noexcept;// override;
  virtual void Unbind() override;

  void AddActor(PLAOBJActor *aActor);
  void RemoveActor(PLAOBJActor *aActor);
  void RemoveFromParentActor();
  void Input(const PLAInput *aInput);

  void Init();
  void Update();
  void Appear();
  void Disappear();

  PLAAGTActor AssignAgent();

  void PrintActors() const;

  const char *GetActorTypeName() const;

  bool IsCollideWithActor(const PLAOBJActor *aActor) const;
  bool IsCollideWithPoint(PLAPoint aPoint) const;

  const std::list<PLAOBJActor *> *GetActors() const { return &_actors; };
  const PLAVec3f &GetPivot() const { return _pivot; };
  void SetPivot(const PLAVec3f &aPivot)
  { _pivot = aPivot; this->RefreshLayerOffset(); };
  PLAColor GetColor() const;
  PLATransform GetTransform() const;
  const PLAOBJLayer *GetLayer() const { return _layer; }
  PLAVec3f GetSize() const { return _layer->GetSize(); };
  void GetSize(PLAVec3f *aSize) const { return _layer->GetSize(aSize); };
  const PLAVec3f &GetLayerOffset() const { return _layer->GetOffset(); };

  PLALayerType GetLayerType() const { return _layer->GetLayerType(); };

  size_t GetNumberOfActors() { return _actors.size(); };

  class PLALYRPoint *RefLYRPoint();
  class PLALYRLine *RefLYRLine();
  class PLALYRRect *RefLYRRect();
  class PLALYRCircle *RefLYRCircle();
  class PLALYRTile *RefLYRTile();
  PLAOBJActor *RefResponsiveActor(const PLAInputDeviceType aDeviceType,
                                  const PLAInputSignalCode aSignalCode);
  PLAOBJActor *RefResponsiveActorWithPoint(const PLAPoint &aPoint,
                                           const PLAInputDeviceType aDeviceType,
                                           const PLAInputSignalCode aSignalCode);

  void SetColor(const PLAColor &aColor)
  { _color = aColor; };
  void SetTransform(const PLATransform &aTransform)
  { _transform = aTransform; };
  virtual void SetSize(const PLAVec3f &aSize)
  { _layer->SetSize(aSize, _pivot); this->RefreshLayerOffset(); };

  void SetTranslation(const PLAVec3f &aTranslation)
  { _transform.translation = aTranslation; };
  void SetRotation(const PLAVec3f &aRotation)
  { _transform.rotation = aRotation; };
  void SetScale(const PLAVec3f &aScale)
  { _transform.scale = aScale; };

  void SetFunction(PLAFunctionCode::Actor aKey,
                   const std::function<void(PLAOBJActor *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void AddTileMotion(const PLAVec2s &aAddress, PLATMLMotion *aThread);

private:
  void OnUpdate();
  void RefreshLayerOffset();

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

};

#endif // PLAIN_ENGINE_PLAOBJACTOR_HPP
