//
// Created by Kentaro Kawai on 2021/05/09.
//

#ifndef ANHR_PLAIMAGECLIP_HPP
#define ANHR_PLAIMAGECLIP_HPP

#include "PLAObject.hpp"
#include "PLAImage.hpp"
#include "Type/PLARect.hpp"

class PLAImageClip : public PLAObject
{
  const PLAImage *_image = nullptr;
  PLARect _clip = kPLARectNone;
  PLARect _normalizedClip = kPLARectNone;

protected:
  PLAImageClip(const PLAImage *aImage, const PLARect &aClip);

public:
  PLAImageClip() = delete;
  static PLAImageClip *Create(const std::string &aImageName);
  static PLAImageClip *Create(const std::string &aImageName,
                              const PLARect &aClip);

  ~PLAImageClip();

  const PLAImage *GetImage() const { return _image; };
  const PLARect &GetClip() const { return _clip; };
  const PLARect &GetNormalizedClip() const { return _normalizedClip; };

  void SetClip(const PLARect &aClip);
  void SetNormalizedClip(const PLARect &aNormalizedClip);

private:
  void UpdateClip(const PLARect &aNormalizedClip);
  void UpdateNormalizedClip(const PLARect &aClip);
};

#endif //ANHR_PLAIMAGECLIP_HPP
