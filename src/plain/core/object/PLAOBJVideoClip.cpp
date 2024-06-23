#include "plain/core/object/PLAOBJVideoClip.hpp"
#include "plain/core/agent/PLAAGTVideoClip.hpp"

PLAOBJVideoClip *PLAOBJVideoClip::Create(const PLAString &aVideoName)
{
  return PLAOBJVideoClip::Create(aVideoName, kPLARangeNone);
}

PLAOBJVideoClip *PLAOBJVideoClip::Create(const PLAString &aVideoName,
                                         const PLARange &aFrameClip,
                                         const PLARect &aPixelClip)
{
  const PLAOBJVideo *video = nullptr;//PLAOBJVideo::CreateRaw(aVideoName);
  PLAOBJVideoClip *videoClip = new PLAOBJVideoClip(video, aFrameClip, aPixelClip);
  videoClip->Bind();
  return videoClip;
}

PLAOBJVideoClip *PLAOBJVideoClip::Object(const PLAString &aObjectName)
{
  return static_cast<PLAOBJVideoClip *>
  (PLAObject::Object(PLAObjectType::VideoClip, aObjectName));
}

PLAOBJVideoClip *PLAOBJVideoClip::Object(PLAId aObjectId)
{
  return static_cast<PLAOBJVideoClip *>
  (PLAObject::Object(PLAObjectType::VideoClip, aObjectId));
}

PLAOBJVideoClip::PLAOBJVideoClip(const PLAOBJVideo *aVideo,
                                 const PLARange &aFrameClip,
                                 const PLARect &aPixelClip,
                                 PLAObjectType aType) :
PLAOBJImageClip(nullptr, aPixelClip, aType), _video(aVideo), _clip(aFrameClip)
{
  this->UpdateNormalizedFrameClip(aFrameClip);
}

PLAOBJVideoClip::~PLAOBJVideoClip()
{

}

PLAAGTVideoClip PLAOBJVideoClip::AssignAgent()
{
  return PLAAGTVideoClip(this);
}

void PLAOBJVideoClip::SetFrameClip(const PLARange &aClip)
{
  _clip = aClip;
  this->UpdateNormalizedFrameClip(aClip);
}

void PLAOBJVideoClip::SetNormalizedFrameClip(const PLARange &aClip)
{
  _normalizedClip = aClip;
  this->UpdateFrameClip(aClip);
}

void PLAOBJVideoClip::UpdateFrameClip(const PLARange &aClip)
{
  /*
  _clip.pos.x = _video->GetSize().x * aClip.pos.x;
  _clip.pos.y = _video->GetSize().y * aClip.pos.y;
  _clip.size.x = _video->GetSize().x * aClip.pos.x;
  _clip.size.y = _video->GetSize().y * aClip.pos.y;
  */
}

void PLAOBJVideoClip::UpdateNormalizedFrameClip(const PLARange &aClip)
{
  /*
  _normalizedClip.pos.x = aClip.pos.x / _video->GetSize().x;
  _normalizedClip.pos.y = aClip.pos.y / _video->GetSize().y;
  _normalizedClip.size.x = aClip.size.x / _video->GetSize().x;
  _normalizedClip.size.y = aClip.size.y / _video->GetSize().y;
  */
}
