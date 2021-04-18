//
// Created by Kentaro Kawai on 2021/03/17.
//

#include "PLAResource.hpp"

PLAResource::PLAResource(const std::string &aPath) :
  PLAObject(PLAObjectType::Resource),
  _path(aPath) {
}

PLAResource::~PLAResource() noexcept {

}

void PLAResource::AllocData() {
  size_t dataSize = this->GetDataSize();
  _data = new uint8_t[dataSize];
  FILE *fp;

  if ((fp = fopen(_path.c_str(), "rb")) != nullptr) {
    fread(_data, dataSize, 1, fp);
    fclose(fp);
    int result = fread(_data, dataSize, 1, fp);
    PLA_PRINT("result : %d\n", result);
  }
  else {
    perror(_path.c_str());
  }
}

void PLAResource::ReleaseData() {
  //PLA_DELETE_ARRAY(_data)
}

//-- PLARSCImage --/////////////////////////////////////////////////////////////

PLARSCImage *PLARSCImage::Create(const std::string &aPath, size_t aWidth, size_t aHeight)
{
  PLARSCImage *image = new PLARSCImage(aPath, aWidth, aHeight);
  PLAObject::Manager::Ref()->Bind(image);
  return image;
}

PLARSCImage::PLARSCImage(const std::string &aPath, size_t aWidth, size_t aHeight) :
  PLAResource(aPath), _width(aWidth), _height(aHeight)
{

}

PLARSCImage::~PLARSCImage()
{

}

size_t PLARSCImage::GetDataSize() {
  return _width * _height * 4;
}
