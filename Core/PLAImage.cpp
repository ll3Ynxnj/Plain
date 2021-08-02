#include "PLAImage.hpp"

PLAImage *PLAImage::CreateRaw(const std::string &aName)
{
  PLAImage *image = new PLAImage(aName, PLAImageSize(1024), PLAImageType::Raw);
  PLAObject::Bind(image);
  return image;
}

PLAImage::PLAImage(const std::string &aName, const PLAImageSize &aSize,
                   PLAImageType aType) :
  PLAObject(PLAObjectType::Image),
  _resource(PLAResource::Manager::GetInstance()->GetResource(aName)),
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
