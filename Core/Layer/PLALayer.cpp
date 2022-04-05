#include "PLALayer.hpp"
#include "Core/Class/PLAError.hpp"

/*
Layer *Layer::Create(const Layer &aLayer)
{
  Layer *layer = nullptr;
  switch (aLayer.GetLayerType())
  {
    case PLALayerType::Point :
      layer = new PLALYRPoint(static_cast<const PLALYRPoint &>(aLayer));
      break;
    case PLALayerType::Line :
      layer = new PLALYRLine(static_cast<const PLALYRLine  &>(aLayer));
      break;
    case PLALayerType::Rect :
      layer = new PLALYRRect(static_cast<const PLALYRRect &>(aLayer));
      break;
    case PLALayerType::Circle :
      layer = new PLALYRCircle(static_cast<const PLALYRCircle &>(aLayer));
      break;
    default :
      PLA_ERROR_ISSUE(PLAErrorType::Assert, "Detected unexpected PLALayerType.");
      break;
  }
  GRABinder<PLAObject>::Error error(GRABinder<PLAObject>::Error::None);
  PLAObject::Manager::RefInstance()->Bind(layer, &error);
  return layer;
}
 */

PLALayer::PLALayer(PLALayerType aType, const PLAVec3 &aOffset) :
PLAObject(PLAObjectType::Layer),
_type(aType), _offset(aOffset)
{

}

PLALayer::~PLALayer()
{

}
