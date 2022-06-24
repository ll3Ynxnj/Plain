#include "PLAOBJImage.hpp"

PLAOBJImage *PLAOBJImage::CreateRaw(const PLAString &aName)
{
  PLAOBJImage *image = new PLAOBJImage(aName, PLAOBJImageSize(1024), PLAOBJImageType::Raw);
  image->Bind();
  return image;
}

PLAOBJImage::PLAOBJImage(const PLAString &aName, const PLAOBJImageSize &aSize,
                   PLAOBJImageType aType) :
  PLAObject(PLAObjectType::Image),
  _resource(PLAOBJResource::Manager::Instance()->GetResource(aName)),
  _size(aSize), _type(aType)
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
