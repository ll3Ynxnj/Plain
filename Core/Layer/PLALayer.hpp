#ifndef PLAIN_ENGINE_PLALAYER_HPP
#define PLAIN_ENGINE_PLALAYER_HPP

#include "PLAObject.hpp"
#include "PLALayerType.hpp"
#include "PLAImageClip.hpp"
#include "PLAMotion.hpp"
#include "Type/PLAVector.hpp"
#include "Type/PLAPoint.hpp"
#include "Type/PLALine.hpp"
#include "Type/PLAPoint.hpp"
#include "Type/PLACircle.hpp"

class PLALayer : public PLAObject
{
  PLALayerType _type = PLALayerType::None;
  PLAVec3 _offset = kPLAVec3None;

protected:
  PLALayer(PLALayerType aType, const PLAVec3 &aOffset);//, const std::string &aName);

public:
  //static Layer *Create(const Layer &aLayer);

  PLALayer() = delete;
  virtual ~PLALayer();

  virtual void UpdateMotion() {};

  PLALayerType GetLayerType() const { return _type; };
  const PLAVec3 &GetOffset() const { return _offset; };
  void SetOffset(const PLAVec3 &aOffset) { _offset = aOffset; }

  virtual PLAVec3 GetSize() const = 0;
  virtual void GetSize(PLAVec3 *aSize) const = 0;
  virtual void SetSize(const PLAVec3 &aSize, const PLAVec3 &aPivot) = 0;

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const = 0;
  virtual bool IsCollideWithLine(const PLALine &aLine) const = 0;
  virtual bool IsCollideWithRect(const PLARect &aRect) const = 0;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const = 0;
};

#endif // PLAIN_ENGINE_PLALAYER_HPP
