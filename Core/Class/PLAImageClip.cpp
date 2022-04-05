#include "PLAImageClip.hpp"

PLAImageClip *PLAImageClip::Create(const std::string &aImageName)
{
  PLAImageClip::Create(aImageName, kPLARectNorm);
}

PLAImageClip *PLAImageClip::Create(const std::string &aImageName,
                                   const PLARect &aClip)
{
  const PLAImage *image = PLAImage::CreateRaw(aImageName);
  PLAImageClip *imageClip = new PLAImageClip(image, aClip);
  imageClip->Bind();
  return imageClip;
}

PLAImageClip::PLAImageClip(const PLAImage *aImage, const PLARect &aClip) :
PLAObject(PLAObjectType::ImageClip), _image(aImage), _clip(aClip)
{
  this->UpdateNormalizedClip(aClip);
}

PLAImageClip::~PLAImageClip()
{

}

void PLAImageClip::SetClip(const PLARect &aClip)
{
  _clip = aClip;
  this->UpdateNormalizedClip(aClip);
}

void PLAImageClip::SetNormalizedClip(const PLARect &aNormalizedClip)
{
  _normalizedClip = aNormalizedClip;
  this->UpdateClip(aNormalizedClip);
}

void PLAImageClip::UpdateClip(const PLARect &aNormalizedClip)
{
  _clip.pos.x = _image->GetSize().x * aNormalizedClip.pos.x;
  _clip.pos.y = _image->GetSize().y * aNormalizedClip.pos.y;
  _clip.size.x = _image->GetSize().x * aNormalizedClip.pos.x;
  _clip.size.y = _image->GetSize().y * aNormalizedClip.pos.y;
}

void PLAImageClip::UpdateNormalizedClip(const PLARect &aClip)
{
  _normalizedClip.pos.x = aClip.pos.x / _image->GetSize().x;
  _normalizedClip.pos.y = aClip.pos.y / _image->GetSize().y;
  _normalizedClip.size.x = aClip.size.x / _image->GetSize().x;
  _normalizedClip.size.y = aClip.size.y / _image->GetSize().y;
}
