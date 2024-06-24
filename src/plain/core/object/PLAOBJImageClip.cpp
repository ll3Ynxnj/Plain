#include "plain/core/object/PLAOBJImageClip.hpp"
#include "plain/core/agent/PLAAGTImageClip.hpp"

PLAOBJImageClip *PLAOBJImageClip::Create(const PLAString &aImageName)
{
  return PLAOBJImageClip::Create(aImageName, kPLARectNorm);
}

PLAOBJImageClip *PLAOBJImageClip::Create(const PLAString &aImageName,
                                         const PLARect &aClip)
{
  const PLAOBJImage *image = PLAOBJImage::CreateRaw(aImageName);
  PLAOBJImageClip *imageClip = new PLAOBJImageClip(image, aClip);
  imageClip->Bind();
  return imageClip;
}

PLAOBJImageClip *PLAOBJImageClip::Object(const PLAString &aObjectName)
{
  return static_cast<PLAOBJImageClip *>
  (PLAObject::Object(PLAObjectType::ImageClip, aObjectName));
}

PLAOBJImageClip *PLAOBJImageClip::Object(PLAId aObjectId)
{
  return static_cast<PLAOBJImageClip *>
  (PLAObject::Object(PLAObjectType::ImageClip, aObjectId));
}

PLAOBJImageClip::PLAOBJImageClip(const PLAOBJImage *aImage,
                                 const PLARect &aClip,
                                 PLAObjectType aType) :
PLAObject(aType), _image(aImage), _clip(aClip)
{
  this->UpdateNormalizedPixelClip(aClip);
}

PLAOBJImageClip::~PLAOBJImageClip()
{

}

PLAAGTImageClip PLAOBJImageClip::AssignAgent()
{
  return PLAAGTImageClip(this);
}

void PLAOBJImageClip::SetPixelClip(const PLARect &aClip)
{
  _clip = aClip;
  this->UpdateNormalizedPixelClip(aClip);
}

void PLAOBJImageClip::SetNormalizedPixelClip(const PLARect &aClip)
{
  _normalizedClip = aClip;
  this->UpdatePixelClip(aClip);
}

void PLAOBJImageClip::UpdatePixelClip(const PLARect &aClip)
{
  if (!_image) { return; }
  _clip.pos.x = _image->GetSize().x * aClip.pos.x;
  _clip.pos.y = _image->GetSize().y * aClip.pos.y;
  _clip.size.x = _image->GetSize().x * aClip.pos.x;
  _clip.size.y = _image->GetSize().y * aClip.pos.y;
}

void PLAOBJImageClip::UpdateNormalizedPixelClip(const PLARect &aClip)
{
  if (!_image) { return; }
  _normalizedClip.pos.x = aClip.pos.x / _image->GetSize().x;
  _normalizedClip.pos.y = aClip.pos.y / _image->GetSize().y;
  _normalizedClip.size.x = aClip.size.x / _image->GetSize().x;
  _normalizedClip.size.y = aClip.size.y / _image->GetSize().y;
}
