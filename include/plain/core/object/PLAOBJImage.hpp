#ifndef PLAIN_ENGINE_PLAOBJIMAGE_HPP
#define PLAIN_ENGINE_PLAOBJIMAGE_HPP

#include <functional>
#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJResource.hpp"
#include "plain/core/PLAImageType.hpp"
#include "grain/primitive/GRAPRMVector.hpp"

using PLAOBJImageSize = GRAVec2<PLASize>;
static const PLAOBJImageSize kPLAOBJImageSizeNone = PLAOBJImageSize(0);

class PLAOBJImage : public PLAObject
{
public:
  using OnReleasedCallback = std::function<void()>;

private:
  const PLAOBJResource *_resource = nullptr;
  PLAOBJImageSize _size = kPLAOBJImageSizeNone;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-private-field"
  PLAImageType _type = PLAImageType::None;
#pragma clang diagnostic pop
  mutable OnReleasedCallback _onReleasedCallback = nullptr;

public:
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
  //virtual size_t GetDataSize() const;

  void SetOnReleasedCallback(OnReleasedCallback aCallback) const
  { _onReleasedCallback = aCallback; }
  void NotifyReleased() const;
};

#endif //PLAIN_ENGINE_PLAOBJIMAGE_HPP
