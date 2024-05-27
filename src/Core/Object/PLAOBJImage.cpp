#include "Core/Object/PLAOBJImage.hpp"

#include <cmath>

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
