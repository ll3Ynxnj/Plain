#ifndef PLAIN_ENGINE_PLAOBJLAYER_HPP
#define PLAIN_ENGINE_PLAOBJLAYER_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/PLALayerType.hpp"
#include "plain/core/object/PLAOBJImageClip.hpp"
#include "plain/core/object/PLAOBJVideoClip.hpp"
#include "plain/core/object/timeline/PLATMLMotionNode.hpp"
#include "plain/core/primitive/PLAPRMVector.hpp"
#include "plain/core/primitive/PLAPRMPoint.hpp"
#include "plain/core/primitive/PLAPRMLine.hpp"
#include "plain/core/primitive/PLAPRMPoint.hpp"
#include "plain/core/primitive/PLAPRMCircle.hpp"

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

  virtual void SetImageClip(PLAOBJImageClip *aImageClip) = 0;
  virtual void SetVideoClip(PLAOBJVideoClip *aVideoClip) = 0;

  virtual bool IsCollideWithPoint(const PLAPoint &aPoint) const = 0;
  virtual bool IsCollideWithLine(const PLALine &aLine) const = 0;
  virtual bool IsCollideWithRect(const PLARect &aRect) const = 0;
  virtual bool IsCollideWithCircle(const PLACircle &aCircle) const = 0;
};

#endif // PLAIN_ENGINE_PLAOBJLAYER_HPP
