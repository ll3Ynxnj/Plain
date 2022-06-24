#ifndef PLAIN_ENGINE_PLAOBJLAYER_HPP
#define PLAIN_ENGINE_PLAOBJLAYER_HPP

#include "Object/PLAObject.hpp"
#include "PLAOBJLayerType.hpp"
#include "Object/PLAOBJImageClip.hpp"
#include "Object/Timeline/PLATMLMotionNode.hpp"
#include "Primitive/PLAPRMVector.hpp"
#include "Primitive/PLAPRMPoint.hpp"
#include "Primitive/PLAPRMLine.hpp"
#include "Primitive/PLAPRMPoint.hpp"
#include "Primitive/PLAPRMCircle.hpp"

class PLAOBJLayer : public PLAObject
{
  PLAOBJLayerType _type = PLAOBJLayerType::None;
  PLAVec3 _offset = kPLAVec3None;

protected:
  PLAOBJLayer(PLAOBJLayerType aType, const PLAVec3 &aOffset);//, const std::string &aName);

public:
  //static Layer *Create(const Layer &aLayer);

  PLAOBJLayer() = delete;
  virtual ~PLAOBJLayer();

  //virtual void UpdateMotionProperties() {};

  PLAOBJLayerType GetLayerType() const { return _type; };
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

#endif // PLAIN_ENGINE_PLAOBJLAYER_HPP
