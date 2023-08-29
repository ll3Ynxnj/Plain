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
#include "Object/Timeline/PLAMotionHolder.hpp"
#include "Object/Timeline/PLATMLMotionNode.hpp"
#include "Object/Timeline/PLATMLMotion.hpp"

#include "PLAFunctionCode.hpp"

class PLAOBJRenderer;
class PLAAGTActor;
class PLAAGTActorForRect;
class PLAAGTActorForCircle;
class PLAAGTActorForTile;

class PLAOBJActor final :
  public PLAObject,
  public PLAInputContext,
  public PLAMotionHolder,
  public PLAOBJPhase::Listener,
  private GRAOBJBinder<PLAOBJActor>::Item
{
  using Binder = GRAOBJBinder<PLAOBJActor>;
  static const std::map<Binder::Error, const char *> kBinderErrorMessages;

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
  PLABool _visible = true;

  GRAOBJFunctor<PLAOBJActor *, PLAFunctionCode::Actor> _functor = GRAOBJFunctor<PLAOBJActor *, PLAFunctionCode::Actor>();

  /// Calculate from pivot. Must be updated when pivot changes.

protected:
  PLAOBJActor(const PLAVec3f &aPivot, const PLAColor &aColor,
              const PLATransform &aTransform, PLAOBJLayer *aLayer);
  PLAOBJActor(const PLAVec3f &aPivot, const PLAColor &aColor,
              const PLATransform &aTransform, PLAOBJLayer *aLayer,
              const PLAString &aName);

public:
  using PLAActorItem = GRAOBJBinder<PLAOBJActor>::Item;
  using PLAActorError = GRAOBJBinder<PLAOBJActor>::Error;

  static const char *GetBinderErrorMessage(Binder::Error aError);
  static PLAOBJActor *Object(const PLAString &aName);
  static PLAOBJActor *Object(PLAId aId);
  static PLAOBJActor *ObjectWithTag(PLAId aTag);

  static PLAOBJActor *CreateRect(const PLAVec2f &aOrigin,
                                 const PLAVec2f &aSize,
                                 const PLAColor &aFillColor,
                                 const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateRect(const PLAVec3f &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLARect &aRect,
                                 const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateRect(const PLAVec3f &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLARect &aRect,
                                 const PLAColor &aFillColor,
                                 const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateRect(const PLAVec3f &aPivot,
                                 const PLAColor &aColor,
                                 const PLATransform &aTransform,
                                 const PLARect &aRect,
                                 const std::string &aImage,
                                 const PLARect &aClip,
                                 const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateCircle(const PLAVec2f &aOrigin,
                                   const PLAFloat aRadius,
                                   const PLAColor &aFillColor,
                                   const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateCircle(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLACircle &aCircle,
                                   const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateCircle(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLACircle &aCircle,
                                   const PLAColor &aFillColor,
                                   const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateCircle(const PLAVec3f &aPivot,
                                   const PLAColor &aColor,
                                   const PLATransform &aTransform,
                                   const PLACircle &aCircle,
                                   const std::string &aImage,
                                   const PLARect &aClip,
                                   const PLAString &aName = kPLAStrUndefined);

  static PLAOBJActor *CreateTile(const PLAVec2f &aOffset,
                                 const std::string &aImageName,
                                 const GRAVec2<PLASize> &aTileSize,
                                 const GRAVec2<PLASize> &aChipSize,
                                 const IPLATileLayerDataSource *aDataSource,
                                 const PLAString &aName = kPLAStrUndefined);

  void Bind() override;

protected:
  void Unbind() override;

public:
  virtual ~PLAOBJActor() noexcept;// override;
  //virtual void Unbind() override;

  // レイヤーの外部からの追加は禁止したい。レイヤは本オブジェクト破棄時に一緒にdeleteされるため。
  // Prohibit adding from outside of the layer. Because the layer is deleted together when this object is destroyed.
  void AddLayer(PLAOBJLayer *aLayer) = delete;

  void AddActor(PLAOBJActor *aActor);
  void RemoveActor(PLAOBJActor *aActor);
  void RemoveFromParentActor();
  void Input(const PLAInput *aInput);

  void Init();
  void Update();
  void Appear();
  void Disappear();

  PLAAGTActor AssignAgent();
  PLAAGTActorForRect AssignAgentForRect();
  PLAAGTActorForCircle AssignAgentForCircle();
  PLAAGTActorForTile AssignAgentForTile();

  PLAId GetActorTag() const;
  void SetActorTag(PLAId aTag);

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
  PLABool IsVisible() const { return _visible; };
  void SetVisible(PLABool aValue) { _visible = aValue; };

  PLALayerType GetLayerType() const { return _layer->GetLayerType(); };

  size_t GetNumberOfActors() { return _actors.size(); };

  class PLALYRPoint *RefLayerForPoint();
  class PLALYRLine *RefLayerForLine();
  class PLALYRRect *RefLayerForRect();
  class PLALYRCircle *RefLayerForCircle();
  class PLALYRTile *RefLayerForTile();
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

  void SetImageClip(PLAOBJImageClip *aClip)
  { _layer->SetImageClip(aClip); };

  void SetFunction(PLAFunctionCode::Actor aKey,
                   const std::function<void(PLAOBJActor *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  //void AddTileMotion(const PLATileDataAddress &aAddress, PLATMLMotion *aThread);

private:
  void OnUpdate();
  void RefreshLayerOffset();

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJActor>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };
    static PLAOBJActor *Actor(const PLAString &aKey);

    ~Manager();

    void Init();

    const PLAOBJActor *GetActor(const PLAString &aName) const;
    void PrintActors() const;
  };
};

#endif // PLAIN_ENGINE_PLAOBJACTOR_HPP
