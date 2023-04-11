#ifndef PLAIN_ENGINE_PLAOBJACTOR_HPP
#define PLAIN_ENGINE_PLAOBJACTOR_HPP

#include <list>
#include <functional>
#include "Object/PLAObject.hpp"
#include "Object/PLAOBJScene.hpp"
#include "Object/Input/PLAInputContext.hpp"
#include "Core/Library/PLALIBCollision.hpp"
#include "PLAOBJActorCollisionCode.hpp"
#include "PLAOBJActorCollisyncCode.hpp"
#include "PLAOBJActorFunctionCode.hpp"
#include "Primitive/PLAPRMColor.hpp"
#include "Primitive/PLAPRMVector.hpp"
#include "Primitive/PLAPRMTransform.hpp"
#include "Object/Layer/PLAOBJLayer.hpp"
#include "Object/Layer/IPLATileLayerDataSource.hpp"
#include "Grain/Object/GRAOBJBinder.hpp"
#include "Object/Timeline/PLATimelineHolder.hpp"
#include "Object/Timeline/PLATMLMotionNode.hpp"
#include "Object/Timeline/PLATMLMotion.hpp"

class PLAOBJRenderer;

class PLAOBJActor final :
  public PLAObject, public PLAInputContext, public PLATimelineHolder,
  public GRAOBJListener<PLAOBJScene, PLAOBJScene::FunctionCode>,
  /*private*/public GRAOBJBinder<PLAOBJActor>::Item
{
public:
  //static void Bind(PLAOBJActor *aObject);
  //static void Unbind(PLAOBJActor *aObject);

private:
  struct CollisionItem
  {
    PLACollision *collision = nullptr;
    bool syncMode[static_cast<unsigned>(PLAOBJActorCollisyncCode::kNumberOfItems)] =
    { false };
  };

  std::list<PLAOBJActor *> _actors = {};
  PLAVec3f _pivot = kPLAVec3fNone;
  PLAColor _color = kPLAColorWhite;
  PLATransform _transform = kPLATransformNorm;
  //-- Not affect child actors
  /*
  PLATMLMotionNode _motion = PLATMLMotionNode();
  std::map<PLATMLMotionType, PLAProperty> _motionProperties =
    std::map<PLATMLMotionType, PLAProperty>();
  */

  PLAOBJLayer *_layer = nullptr;
  //PLAStyle _style = PLAStyle();
  CollisionItem collisions[static_cast<unsigned>(PLAOBJActorCollisionCode::kNumberOfItems)];

  GRAOBJFunctor<PLAOBJActor, PLAOBJActorFunctionCode> _functor = GRAOBJFunctor<PLAOBJActor, PLAOBJActorFunctionCode>();

  /// Calculate from pivot. Must be updated when pivot changes.

protected:
  PLAOBJActor(const PLAVec3f &aPivot,
              const PLAColor &aColor,
              const PLATransform &aTransform,
              PLAOBJLayer *aLayer);//,
           //PLATMLMotionNode *aMotion);

public:
  /*
  static PLAOBJActor *Create(const PLAVec3f &aPivot,
                          const PLAColor &aColor,
                          const PLATransform &aTransform,
                          const Layer &aLayer);
                          */

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
  void Input(const PLAInput *aInput);

  void Init();
  void Update();
  void Appear();
  void Disappear();

  void PrintActors() const;

  const char *GetActorTypeName() const;

  //bool IsCollideWithInput(const PLAInput &aInput) const;
  bool IsCollideWithActor(const PLAOBJActor *aActor) const;
  bool IsCollideWithPoint(PLAPoint aPoint) const;
  //bool IsCollideWithRect(PLARect aRect) const;

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

  PLAOBJLayerType GetLayerType() const { return _layer->GetLayerType(); };

  //const PLAProperty &GetMotionProperty(PLATMLMotionType aType)
  //{ return _motionProperties[aType]; };
  //const PLAStyle *GetLayerStyle() const { return _layer->GetStyle(); }

  //const PLAStyle *GetStyle() const { return &_style; };
  //void SetStyle(const PLAStyle &aStyle) { _style = aStyle; }

  /*
  const PLALYRRect *GetLayerRect() const;
  const PLALYRCircle *GetLayerCircle() const;
  */

  //void AddMotion(PLATMLMotionNode *aMotion);
  /*
  void AddMotion(PLATMLMotionType aType, const PLAProperty &aDistance,
                 PLAFloat aDuration);
  void AddMotionAlpha(PLAFloat aAlpha, PLAFloat aDuration);
  void AddMotionColor(const PLAColor &aColor, PLAFloat aDuration);
  void AddMotionTranslation(const PLAVec3f &aTranslation, PLAFloat aDuration);
  void AddMotionRotation(const PLAVec3f &aRotation, PLAFloat aDuration);
  void AddMotionScale(const PLAVec3f &aScale, PLAFloat aDuration);
   */

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
  //PLAOBJActor *RefActorWithInput(const PLAInput &aInput);

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

  void SetFunction(PLAOBJActorFunctionCode aKey,
                   const std::function<void(PLAOBJActor *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void AddTileMotion(const PLAVec2s &aAddress, PLATMLMotion *aThread);
  //void AddTileMotions(const PLAVec2s &aAddress, const std::vector<PLATMLMotionNode *> &aMotion);
  //void SetTileMotion(const PLAVec2s &aAddress, PLATMLMotionNode *aMotion);

private:
  void OnUpdate();
  //void OnUpdateMotions();

  //void UpdateMotions();
  void RefreshLayerOffset();

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

};

#endif // PLAIN_ENGINE_PLAOBJACTOR_HPP
