#include "PLAImage.hpp"

PLAImage *PLAImage::CreateRaw(const PLAString &aName)
{
  PLAImage *image = new PLAImage(aName, PLAImageSize(1024), PLAImageType::Raw);
  image->Bind();
  return image;
}

PLAImage::PLAImage(const PLAString &aName, const PLAImageSize &aSize,
                   PLAImageType aType) :
  PLAObject(PLAObjectType::Image),
  _resource(PLAResource::Manager::Instance()->GetResource(aName)),
  _size(aSize), _type(aType)
{

}

PLAImage::~PLAImage()
{

}

/*
PLASize PLAImage::GetDataSize() const {
  return _width * _height * 4;
}
 */
