#include "plain/core/object/PLAOBJVideoClip.hpp"
#include "plain/core/agent/PLAAGTVideoClip.hpp"
#include "plain/core/object/PLAOBJImage.hpp"

PLAOBJVideoClip *PLAOBJVideoClip::Create(const PLAString &aVideoName)
{
  return PLAOBJVideoClip::Create(aVideoName, kPLARangeNone);
}

PLAOBJVideoClip *PLAOBJVideoClip::Create(const PLAString &aVideoName,
                                         const PLARange &aFrameClip,
                                         const PLARect &aPixelClip)
{
  // Get existing video object by name
  PLAOBJVideo *video = static_cast<PLAOBJVideo *>(
    PLAObject::Object(PLAObjectType::Video, aVideoName));

  if (!video)
  {
    GRA_PRINT("Video %s not found\n", aVideoName.c_str());
    return nullptr;
  }

  PLAOBJVideoClip *videoClip = new PLAOBJVideoClip(video, aFrameClip, aPixelClip);
  videoClip->Bind();

  // 初期フレームを取得して設定
  videoClip->Update();

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

PLAOBJVideoClip::PLAOBJVideoClip(PLAOBJVideo *aVideo,
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

void PLAOBJVideoClip::Update()
{
  if (!_video) { return; }

  // Update the stream to get next frame
  // This is where stream update happens - when VideoClip is being used
  PLAOBJStream *stream = _video->GetStream();
  if (stream) {
    stream->Update();
  }

  // Get current frame from video (now with updated stream data)
  const PLAOBJImage *currentImage = _video->GetCurrentImage();
  if (!currentImage) { return; }

  // Update the image clip with the current frame
  this->SetImage(currentImage);
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
