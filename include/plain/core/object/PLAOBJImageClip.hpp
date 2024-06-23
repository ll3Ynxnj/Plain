#ifndef PLAIN_ENGINE_PLAOBJIMAGECLIP_HPP
#define PLAIN_ENGINE_PLAOBJIMAGECLIP_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/primitive/PLAPRMRect.hpp"

class PLAAGTImageClip;

class PLAOBJImageClip : public PLAObject
{
  const PLAOBJImage *_image = nullptr;
  PLARect _clip = kPLARectNone;
  PLARect _normalizedClip = kPLARectNone;

protected:
  PLAOBJImageClip(const PLAOBJImage *aImage, const PLARect &aPixelClip,
                  PLAObjectType aType = PLAObjectType::ImageClip);

public:
  PLAOBJImageClip() = delete;
  static PLAOBJImageClip *Create(const PLAString &aImageName);
  static PLAOBJImageClip *Create(const PLAString &aImageName,
                                 const PLARect &aPixelClip);
  static PLAOBJImageClip *Object(const PLAString &aObjectName);
  static PLAOBJImageClip *Object(PLAId aObjectId);

  ~PLAOBJImageClip();

  PLAAGTImageClip AssignAgent();

  const PLAOBJImage *GetImage() const { return _image; }
  const PLARect &GetPixelClip() const { return _clip; }
  const PLARect &GetNormalizedPixelClip() const { return _normalizedClip; }

  void SetPixelClip(const PLARect &aClip);
  void SetNormalizedPixelClip(const PLARect &aClip);

private:
  void UpdatePixelClip(const PLARect &aClip);
  void UpdateNormalizedPixelClip(const PLARect &aClip);
};

#endif //PLAIN_ENGINE_PLAOBJIMAGECLIP_HPP
