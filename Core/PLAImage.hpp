#ifndef PLAIN_PLAIMAGE_HPP
#define PLAIN_PLAIMAGE_HPP

#include "PLAObject.hpp"
#include "PLAResource.hpp"
#include "PLAImageType.hpp"
#include <Grain/Type/GRAVector.hpp>

using PLAImageSize = GRAVec2<PLASize>;
static const PLAImageSize kPLAImageSizeNone = PLAImageSize(0);

class PLAImage : public PLAObject
{
  const PLAResource *_resource = nullptr;
  PLAImageSize _size = kPLAImageSizeNone;
  PLAImageType _type = PLAImageType::None;

public:
  static PLAImage *CreateRaw(const std::string &aName);

  PLAImage(const std::string &aName, const PLAImageSize &aSize,
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
