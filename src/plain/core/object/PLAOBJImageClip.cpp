#include "plain/core/object/PLAOBJImageClip.hpp"
#include "plain/core/agent/PLAAGTImageClip.hpp"

PLAOBJImageClip *PLAOBJImageClip::Create(const PLAString &aImageName)
{
  return PLAOBJImageClip::Create(aImageName, kPLARectNone);
}

PLAOBJImageClip *PLAOBJImageClip::Create(const PLAString &aImageName,
                                         const PLARect &aClip)
{
  const PLAOBJImage *image = PLAOBJImage::Create(aImageName);
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
PLAObject(aType), _clip(aClip)
{
  this->SetImage(aImage);
}

PLAOBJImageClip::~PLAOBJImageClip()
{

}

PLAAGTImageClip PLAOBJImageClip::AssignAgent()
{
  return PLAAGTImageClip(this);
}

void PLAOBJImageClip::SetImage(const PLAOBJImage *aImage)
{
  _image = aImage;

  // NormalizedPixelClipが未設定（サイズが0）の場合、デフォルトで全体を使う
  PLARect normalizedClip = this->GetNormalizedPixelClip();
  if (normalizedClip.size.x == 0 || normalizedClip.size.y == 0) {
    normalizedClip = kPLARectNorm;  // pos=(0,0), size=(1,1)
    _normalizedClip = normalizedClip;
  }

  this->UpdatePixelClip(normalizedClip);
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
  _clip.size.x = _image->GetSize().x * aClip.size.x;
  _clip.size.y = _image->GetSize().y * aClip.size.y;
}

void PLAOBJImageClip::UpdateNormalizedPixelClip(const PLARect &aClip)
{
  if (!_image) { return; }
  _normalizedClip.pos.x = aClip.pos.x / _image->GetSize().x;
  _normalizedClip.pos.y = aClip.pos.y / _image->GetSize().y;
  _normalizedClip.size.x = aClip.size.x / _image->GetSize().x;
  _normalizedClip.size.y = aClip.size.y / _image->GetSize().y;
}
