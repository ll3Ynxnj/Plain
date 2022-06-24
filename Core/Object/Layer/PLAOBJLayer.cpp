#include "PLAOBJLayer.hpp"
#include "Object/PLAOBJError.hpp"

/*
Layer *Layer::Create(const Layer &aLayer)
{
  Layer *layer = nullptr;
  switch (aLayer.GetLayerType())
  {
    case PLAOBJLayerType::Point :
      layer = new PLALYRPoint(static_cast<const PLALYRPoint &>(aLayer));
      break;
    case PLAOBJLayerType::Line :
      layer = new PLALYRLine(static_cast<const PLALYRLine  &>(aLayer));
      break;
    case PLAOBJLayerType::Rect :
      layer = new PLALYRRect(static_cast<const PLALYRRect &>(aLayer));
      break;
    case PLAOBJLayerType::Circle :
      layer = new PLALYRCircle(static_cast<const PLALYRCircle &>(aLayer));
      break;
    default :
      PLA_ERROR_ISSUE(PLAOBJErrorType::Assert, "Detected unexpected PLAOBJLayerType.");
      break;
  }
  GRAOBJBinder<PLAObject>::Error error(GRAOBJBinder<PLAObject>::Error::None);
  PLAObject::Manager::RefInstance()->Bind(layer, &error);
  return layer;
}
 */

PLAOBJLayer::PLAOBJLayer(PLAOBJLayerType aType, const PLAVec3 &aOffset) :
PLAObject(PLAObjectType::Layer),
_type(aType), _offset(aOffset)
{

}

PLAOBJLayer::~PLAOBJLayer()
{

}
