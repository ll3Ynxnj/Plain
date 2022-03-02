#ifndef PLAIN_ENGINE_PLAACTOR_HPP
#define PLAIN_ENGINE_PLAACTOR_HPP

#include <list>
#include <functional>
#include "PLAObject.hpp"
#include "Core/Node/PLAMotion.hpp"
#include "PLAScene.hpp"
#include "Core/Input/PLAInput.hpp"
#include "PLACollision.hpp"
#include "PLAActorCollisionCode.hpp"
#include "PLAActorCollisyncCode.hpp"
#include "PLAActorFunctionCode.hpp"
#include "Type/PLAColor.hpp"
#include "Type/PLAVector.hpp"
#include "Type/PLATransform.hpp"
#include "Layer/PLALayer.hpp"
#include "Layer/IPLALYRTileDataSource.hpp"
#include "Grain/GRABinder.hpp"
#include "Node/PLANodeHolder.hpp"
#include "Node/PLAMotionThread.hpp"

class PLARenderer;

class PLAActor final :
  public PLAObject, public PLAInputContext, public PLANodeHolder,
  public GRAListener<PLAScene, PLAScene::FunctionCode>,
  public GRABinder<PLAActor>::Item
{
public:
  //static void Bind(PLAActor *aObject);
  //static void Unbind(PLAActor *aObject);

private:
  struct CollisionItem
  {
    PLACollision *collision = nullptr;
    bool syncMode[static_cast<unsigned>(PLAActorCollisyncCode::kNumberOfItems)] =
    { false };
  };

  std::list<PLAActor *> _actors = {};
  PLAVec3 _pivot = kPLAVec3None;
  PLAColor _color = kPLAColorWhite;
  PLATransform _transform = kPLATransformNorm;
  //-- Not affect child actors
  /*
  PLAMotion _motion = PLAMotion();
  std::map<PLAMotionType, PLAProperty> _motionProperties =
    std::map<PLAMotionType, PLAProperty>();
  */

  PLALayer *_layer = nullptr;
  //PLAStyle _style = PLAStyle();
  CollisionItem collisions[static_cast<unsigned>(PLAActorCollisionCode::kNumberOfItems)];

  GRAFunctor<PLAActor, PLAActorFunctionCode> _functor = GRAFunctor<PLAActor, PLAActorFunctionCode>();

  /// Calculate from pivot. Must be updated when pivot changes.

protected:
  PLAActor(const PLAVec3 &aPivot,
           const PLAColor &aColor,
           const PLATransform &aTransform,
           PLALayer *aLayer);//,
           //PLAMotion *aMotion);

public:
  /*
  static PLAActor *Create(const PLAVec3 &aPivot,
                          const PLAColor &aColor,
                          const PLATransform &aTransform,
                          const Layer &aLayer);
                          */

  static PLAActor *CreateRect(const PLAVec3 &aPivot,
                              const PLAColor &aColor,
                              const PLATransform &aTransform,
                              const PLARect &aRect);

  static PLAActor *CreateRect(const PLAVec3 &aPivot,
                              const PLAColor &aColor,
                              const PLATransform &aTransform,
                              const PLARect &aRect,
                              const PLAColor &aFillColor);

  static PLAActor *CreateRect(const PLAVec3 &aPivot,
                              const PLAColor &aColor,
                              const PLATransform &aTransform,
                              const PLARect &aRect,
                              const std::string &aImage,
                              const PLARect &aClip);

  static PLAActor *CreateCircle(const PLAVec3 &aPivot,
                                const PLAColor &aColor,
                                const PLATransform &aTransform,
                                const PLACircle &aCircle);

  static PLAActor *CreateCircle(const PLAVec3 &aPivot,
                                const PLAColor &aColor,
                                const PLATransform &aTransform,
                                const PLACircle &aCircle,
                                const PLAColor &aFillColor);

  static PLAActor *CreateCircle(const PLAVec3 &aPivot,
                                const PLAColor &aColor,
                                const PLATransform &aTransform,
                                const PLACircle &aCircle,
                                const std::string &aImage,
                                const PLARect &aClip);

  static PLAActor *CreateTile(const PLAVec2 &aOffset,
                              const std::string &aImageName,
                              const GRAVec2<PLASize> &aTileSize,
                              const GRAVec2<PLASize> &aChipSize,
                              const IPLALYRTileDataSource *aDataSource);

  virtual ~PLAActor() override;

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
  PLAColor GetColor() const;
  PLATransform GetTransform() const;
  const PLALayer *GetLayer() const { return _layer; }
  PLAVec3 GetSize() const { return _layer->GetSize(); };
  void GetSize(PLAVec3 *aSize) const { return _layer->GetSize(aSize); };
  const PLAVec3 &GetLayerOffset() const { return _layer->GetOffset(); };

  PLALayerType GetLayerType() const { return _layer->GetLayerType(); };

  //const PLAProperty &GetMotionProperty(PLAMotionType aType)
  //{ return _motionProperties[aType]; };
  //const PLAStyle *GetLayerStyle() const { return _layer->GetStyle(); }

  //const PLAStyle *GetStyle() const { return &_style; };
  //void SetStyle(const PLAStyle &aStyle) { _style = aStyle; }

  /*
  const PLALYRRect *GetLayerRect() const;
  const PLALYRCircle *GetLayerCircle() const;
  */

  //void AddMotion(PLAMotion *aMotion);
  /*
  void AddMotion(PLAMotionType aType, const PLAProperty &aDistance,
                 PLAFloat aDuration);
  void AddMotionAlpha(PLAFloat aAlpha, PLAFloat aDuration);
  void AddMotionColor(const PLAColor &aColor, PLAFloat aDuration);
  void AddMotionTranslation(const PLAVec3 &aTranslation, PLAFloat aDuration);
  void AddMotionRotation(const PLAVec3 &aRotation, PLAFloat aDuration);
  void AddMotionScale(const PLAVec3 &aScale, PLAFloat aDuration);
   */

  size_t GetNumberOfActors() { return _actors.size(); };

  class PLALYRPoint *RefLYRPoint();
  class PLALYRLine *RefLYRLine();
  class PLALYRRect *RefLYRRect();
  class PLALYRCircle *RefLYRCircle();
  class PLALYRTile *RefLYRTile();
  PLAActor *RefResponsiveActor(const PLAInputDeviceType aDeviceType,
                               const PLAInputSignalCode aSignalCode);
  PLAActor *RefResponsiveActorWithPoint(const PLAPoint &aPoint,
                                        const PLAInputDeviceType aDeviceType,
                                        const PLAInputSignalCode aSignalCode);
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

  void SetFunction(PLAActorFunctionCode aKey,
                   const std::function<void(PLAActor *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); };

  void AddTileMotion(const PLAVec2s &aAddress, PLAMotionThread *aThread);
  //void AddTileMotions(const PLAVec2s &aAddress, const std::vector<PLAMotion *> &aMotion);
  //void SetTileMotion(const PLAVec2s &aAddress, PLAMotion *aMotion);

private:
  void OnUpdate();
  //void OnUpdateMotions();

  //void UpdateMotions();
  void RefreshLayerOffset();
};

#endif // PLAIN_ENGINE_PLAACTOR_HPP
