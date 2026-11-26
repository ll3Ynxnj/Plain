#ifndef PLAIN_ENGINE_PLAOBJIMAGE_HPP
#define PLAIN_ENGINE_PLAOBJIMAGE_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJResource.hpp"
#include "plain/core/PLAImageType.hpp"
#include "grain/primitive/GRAPRMVector.hpp"

using PLAOBJImageSize = GRAVec2<PLASize>;
static const PLAOBJImageSize kPLAOBJImageSizeNone = PLAOBJImageSize(0);

class PLAOBJImage : public PLAObject
{
private:
  const PLAOBJResource *_resource = nullptr;
  /// The resource CreateFromMemory made for this image alone. UpdateData writes into it.
  PLAOBJResource *_ownedResource = nullptr;
  PLAOBJImageSize _size = kPLAOBJImageSizeNone;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
  PLAImageType _type = PLAImageType::None;
#pragma clang diagnostic pop

public:
  static PLAOBJImage *Create(const PLAString &aName);
  static PLAOBJImage *CreateRaw(const PLAString &aName);
  static PLAOBJImage *CreateFromMemory(const PLAString &aName, const PLAUInt8 *aData,
                                       const PLAOBJImageSize &aSize, PLAImageType aType);

  PLAOBJImage(const PLAString &aName, const PLAOBJResource *aResource,
              const PLAOBJImageSize &aSize, PLAImageType aType);
  ~PLAOBJImage();

  const PLAOBJImageSize &GetSize() const { return _size; };
  /*
  PLASize GetWidth() const { return _width; };
  PLASize GetHeight() const { return _height; };
   */

  const PLAUInt8 *GetResourceData() const { return _resource->GetData(); }
  uint64_t GetRevision() const { return _resource->GetRevision(); }

  /// Replace the pixels (RGBA, 4 bytes per pixel) of an image made by CreateFromMemory, in place.
  /// The revision changes, so a texture made from the image uploads the new pixels.
  void UpdateData(const PLAUInt8 *aData, const PLAOBJImageSize &aSize);
  //virtual size_t GetDataSize() const;
};

#endif //PLAIN_ENGINE_PLAOBJIMAGE_HPP
