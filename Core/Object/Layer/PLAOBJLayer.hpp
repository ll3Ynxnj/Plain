#ifndef PLAIN_ENGINE_PLAOBJLAYER_HPP
#define PLAIN_ENGINE_PLAOBJLAYER_HPP

#include "Object/PLAObject.hpp"
#include "PLALayerType.hpp"
#include "Object/PLAOBJImageClip.hpp"
#include "Object/Timeline/PLATMLMotionNode.hpp"
#include "Primitive/PLAPRMVector.hpp"
#include "Primitive/PLAPRMPoint.hpp"
#include "Primitive/PLAPRMLine.hpp"
#include "Primitive/PLAPRMPoint.hpp"
#include "Primitive/PLAPRMCircle.hpp"

class PLAOBJLayer : public PLAObject
{
  PLALayerType _type = PLALayerType::None;
  PLAVec3f _offset = kPLAVec3fNone;

protected:
  PLAOBJLayer(PLALayerType aType, const PLAVec3f &aOffset);//, const std::string &aName);

public:
  //static Layer *Create(const Layer &aLayer);

  PLAOBJLayer() = delete;
  virtual ~PLAOBJLayer();

  //virtual void UpdateMotionProperties() {};

  PLALayerType GetLayerType() const { return _type; };
  const PLAVec3f &GetOffset() const { return _offset; };
  void SetOffset(const PLAVec3f &aOffset) { _offset = aOffset; }

  virtual PLAVec3f GetSize() const = 0;
  virtual void GetSize(PLAVec3f *aSize) const = 0;
  virtual void SetSize(const PLAVec3f &aSize, const PLAVec3f &aPivot) = 0;

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const = 0;
  virtual bool IsCollideWithLine(const PLALine &aLine) const = 0;
  virtual bool IsCollideWithRect(const PLARect &aRect) const = 0;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const = 0;
};

#endif // PLAIN_ENGINE_PLAOBJLAYER_HPP
