#ifndef PLAIN_ENGINE_PLAOBJIMAGECLIP_HPP
#define PLAIN_ENGINE_PLAOBJIMAGECLIP_HPP

#include "PLAObject.hpp"
#include "PLAOBJImage.hpp"
#include "Primitive/PLAPRMRect.hpp"

class PLAAGTImageClip;

class PLAOBJImageClip : public PLAObject
{
  const PLAOBJImage *_image = nullptr;
  PLARect _clip = kPLARectNone;
  PLARect _normalizedClip = kPLARectNone;

protected:
  PLAOBJImageClip(const PLAOBJImage *aImage, const PLARect &aClip);

public:
  PLAOBJImageClip() = delete;
  static PLAOBJImageClip *Create(const PLAString &aImageName);
  static PLAOBJImageClip *Create(const PLAString &aImageName,
                                 const PLARect &aClip);
  static PLAOBJImageClip *Object(const PLAString &aName);
  static PLAOBJImageClip *Object(PLAId aId);

  ~PLAOBJImageClip();

  PLAAGTImageClip AssignAgent();

  const PLAOBJImage *GetImage() const { return _image; };
  const PLARect &GetClip() const { return _clip; };
  const PLARect &GetNormalizedClip() const { return _normalizedClip; };

  void SetClip(const PLARect &aClip);
  void SetNormalizedClip(const PLARect &aNormalizedClip);

private:
  void UpdateClip(const PLARect &aNormalizedClip);
  void UpdateNormalizedClip(const PLARect &aClip);
};

#endif //PLAIN_ENGINE_PLAOBJIMAGECLIP_HPP
