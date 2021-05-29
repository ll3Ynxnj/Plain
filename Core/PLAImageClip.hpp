//
// Created by Kentaro Kawai on 2021/05/09.
//

#ifndef ANHR_PLAIMAGECLIP_HPP
#define ANHR_PLAIMAGECLIP_HPP

#include "PLAObject.hpp"
#include "PLAResource.hpp"

class PLAImageClip : public PLAObject
{
  const PLARSCImage *_image = nullptr;
  PLARect _clip = kPLARectNone;
  PLARect _normalizedClip = kPLARectNone;

protected:
  PLAImageClip(const PLARSCImage *aImage, const PLARect &aClip);

public:
  PLAImageClip() = delete;
  static PLAImageClip *Create(const std::string &aImageName, const PLARect &aClip);

  ~PLAImageClip();

  const PLARSCImage *GetImage() const { return _image; };
  const PLARect &GetClip() const { return _clip; };
  const PLARect &GetNormalizedClip() const { return _normalizedClip; };

  void SetClip(const PLARect &aClip);
  void SetNormalizedClip(const PLARect &aNormalizedClip);

private:
  void UpdateClip();
  void UpdateNormalizedClip();
};

#endif //ANHR_PLAIMAGECLIP_HPP
