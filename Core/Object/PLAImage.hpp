#ifndef PLAIN_PLAIMAGE_HPP
#define PLAIN_PLAIMAGE_HPP

#include "PLAObject.hpp"
#include "PLAResource.hpp"
#include "PLAImageType.hpp"
#include "Grain/Primitive/GRAVector.hpp"

using PLAImageSize = GRAVec2<PLASize>;
static const PLAImageSize kPLAImageSizeNone = PLAImageSize(0);

class PLAImage : public PLAObject
{
  const PLAResource *_resource = nullptr;
  PLAImageSize _size = kPLAImageSizeNone;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
  PLAImageType _type = PLAImageType::None;
#pragma clang diagnostic pop

public:
  static PLAImage *CreateRaw(const PLAString &aName);

  PLAImage(const PLAString &aName, const PLAImageSize &aSize,
           PLAImageType aType);
  ~PLAImage();

  const PLAImageSize &GetSize() const { return _size; };
  /*
  PLASize GetWidth() const { return _width; };
  PLASize GetHeight() const { return _height; };
   */

  const PLAUInt8 *GetResourceData() const { return _resource->GetData(); }
  //virtual size_t GetDataSize() const;
};

#endif //PLAIN_PLAIMAGE_HPP
