#ifndef PLAIN_ENGINE_PLAOBJIMAGE_HPP
#define PLAIN_ENGINE_PLAOBJIMAGE_HPP

#include "PLAObject.hpp"
#include "PLAOBJResource.hpp"
#include "PLAOBJImageType.hpp"
#include "Grain/Primitive/GRAPRMVector.hpp"

using PLAOBJImageSize = GRAVec2<PLASize>;
static const PLAOBJImageSize kPLAOBJImageSizeNone = PLAOBJImageSize(0);

class PLAOBJImage : public PLAObject
{
  const PLAOBJResource *_resource = nullptr;
  PLAOBJImageSize _size = kPLAOBJImageSizeNone;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
  PLAOBJImageType _type = PLAOBJImageType::None;
#pragma clang diagnostic pop

public:
  static PLAOBJImage *CreateRaw(const PLAString &aName);

  PLAOBJImage(const PLAString &aName, const PLAOBJImageSize &aSize,
           PLAOBJImageType aType);
  ~PLAOBJImage();

  const PLAOBJImageSize &GetSize() const { return _size; };
  /*
  PLASize GetWidth() const { return _width; };
  PLASize GetHeight() const { return _height; };
   */

  const PLAUInt8 *GetResourceData() const { return _resource->GetData(); }
  //virtual size_t GetDataSize() const;
};

#endif //PLAIN_ENGINE_PLAOBJIMAGE_HPP
