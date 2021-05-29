#include "PLAImageClip.hpp"

PLAImageClip *PLAImageClip::Create(const std::string &aImageName,
                                   const PLARect &aClip)
{
  const PLARSCImage *image = static_cast<const PLARSCImage *>
  (PLAResource::Manager::GetInstance()->GetResource(aImageName));

  PLAImageClip *imageClip = new PLAImageClip(image, aClip);
  PLAObject::Bind(imageClip);
  return imageClip;
}

PLAImageClip::PLAImageClip(const PLARSCImage *aImage, const PLARect &aClip) :
PLAObject(PLAObjectType::ImageClip), _image(aImage), _clip(aClip)
{
  this->UpdateNormalizedClip();
}

PLAImageClip::~PLAImageClip()
{

}

void PLAImageClip::SetClip(const PLARect &aClip)
{
  _clip = aClip;
  this->UpdateNormalizedClip();
}

void PLAImageClip::SetNormalizedClip(const PLARect &aNormalizedClip)
{
  _normalizedClip = aNormalizedClip;
  this->UpdateClip();
}

void PLAImageClip::UpdateClip()
{
  _clip.pos.x = _image->GetWidth() * _normalizedClip.pos.x;
  _clip.pos.y = _image->GetHeight() * _normalizedClip.pos.y;
  _clip.size.x = _image->GetWidth() * _normalizedClip.pos.x;
  _clip.size.y = _image->GetHeight() * _normalizedClip.pos.y;
}

void PLAImageClip::UpdateNormalizedClip()
{
  _normalizedClip.pos.x = _clip.pos.x / _image->GetWidth();
  _normalizedClip.pos.y = _clip.pos.y / _image->GetHeight();
  _normalizedClip.size.x = _clip.size.x / _image->GetWidth();
  _normalizedClip.size.y = _clip.size.y / _image->GetHeight();
}
