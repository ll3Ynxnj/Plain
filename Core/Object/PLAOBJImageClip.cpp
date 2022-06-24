#include "PLAOBJImageClip.hpp"

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

PLAOBJImageClip::PLAOBJImageClip(const PLAOBJImage *aImage, const PLARect &aClip) :
PLAObject(PLAObjectType::ImageClip), _image(aImage), _clip(aClip)
{
  this->UpdateNormalizedClip(aClip);
}

PLAOBJImageClip::~PLAOBJImageClip()
{

}

void PLAOBJImageClip::SetClip(const PLARect &aClip)
{
  _clip = aClip;
  this->UpdateNormalizedClip(aClip);
}

void PLAOBJImageClip::SetNormalizedClip(const PLARect &aNormalizedClip)
{
  _normalizedClip = aNormalizedClip;
  this->UpdateClip(aNormalizedClip);
}

void PLAOBJImageClip::UpdateClip(const PLARect &aNormalizedClip)
{
  _clip.pos.x = _image->GetSize().x * aNormalizedClip.pos.x;
  _clip.pos.y = _image->GetSize().y * aNormalizedClip.pos.y;
  _clip.size.x = _image->GetSize().x * aNormalizedClip.pos.x;
  _clip.size.y = _image->GetSize().y * aNormalizedClip.pos.y;
}

void PLAOBJImageClip::UpdateNormalizedClip(const PLARect &aClip)
{
  _normalizedClip.pos.x = aClip.pos.x / _image->GetSize().x;
  _normalizedClip.pos.y = aClip.pos.y / _image->GetSize().y;
  _normalizedClip.size.x = aClip.size.x / _image->GetSize().x;
  _normalizedClip.size.y = aClip.size.y / _image->GetSize().y;
}
