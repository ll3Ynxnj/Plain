#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/object/PLAOBJResource.hpp"

#include <cmath>

PLAOBJImage *PLAOBJImage::Create(const PLAString &aName)
{
  auto resource = PLAOBJResource::Manager::Instance()->GetResource(aName);
  if (!resource) {
    return nullptr;
  }

  PLAImageType imageType = resource->GetImageType();
  PLAOBJImageSize imageSize;

  if (imageType == PLAImageType::Png || imageType == PLAImageType::Jpg) {
    // Use dimensions from decoded image
    imageSize = PLAOBJImageSize(resource->GetImageWidth(), resource->GetImageHeight());
  } else {
    // RAW: assume square image (same as CreateRaw)
    auto resourceSize = resource->GetSize();
    imageSize = PLAOBJImageSize(sqrt(resourceSize / 4));
    imageType = PLAImageType::Raw;
  }

  PLAOBJImage *image = new PLAOBJImage(aName, resource, imageSize, imageType);
  image->Bind();
  return image;
}

PLAOBJImage *PLAOBJImage::CreateRaw(const PLAString &aName)
{
  // 注意：以下のRawファイルであることを前提としている
  //  - 1ピクセルあたりのデータ量が4バイト
  //  - 縦横のピクセル数が等しい
  // CAUTION: The following assumes that the file is Raw
  //  - 4 bytes per pixel
  //  - The number of pixels in the vertical and horizontal directions are equal

  auto resource = PLAOBJResource::Manager::Instance()->GetResource(aName);
  auto resourceSize = resource->GetSize();
  auto imageSize = PLAOBJImageSize(sqrt(resourceSize / 4));

  PLAOBJImage *image = new PLAOBJImage(aName, resource, imageSize,
                                       PLAImageType::Raw);

  image->Bind();
  return image;
}

PLAOBJImage *PLAOBJImage::CreateFromMemory(const PLAString &aName, const PLAUInt8 *aData,
                                           const PLAOBJImageSize &aSize, PLAImageType aType)
{
  // メモリからリソースを作成
  PLASize dataSize = aSize.x * aSize.y * 4; // RGBA 4バイト/ピクセル
  auto resource = PLAOBJResource::CreateFromMemory(aName + "_resource", aData, dataSize);

  PLAOBJImage *image = new PLAOBJImage(aName, resource, aSize, aType);
  image->Bind();
  return image;
}

PLAOBJImage::PLAOBJImage(const PLAString &aName,
                         const PLAOBJResource *aResource,
                         const PLAOBJImageSize &aSize, PLAImageType aType) :
  PLAObject(PLAObjectType::Image),
  _resource(aResource),
  _size(aSize),
  _type(aType)
{

}

PLAOBJImage::~PLAOBJImage()
{

}

/*
PLASize PLAOBJImage::GetDataSize() const {
  return _width * _height * 4;
}
 */
