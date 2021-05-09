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
    GRA_PRINT("result : %d\n", result);
  }
  else {
    perror(_path.c_str());
  }
}

void PLAResource::ReleaseData() {
  //GRA_DELETE_ARRAY(_data)
}

//-- PLARSCImage --/////////////////////////////////////////////////////////////

PLARSCImage *PLARSCImage::Create(const std::string &aPath, size_t aWidth, size_t aHeight)
{
  PLARSCImage *item = new PLARSCImage(aPath, aWidth, aHeight);
  GRABinder::Error error(GRABinder::Error::None);
  PLAObject::Manager::RefInstance()->Bind(item, &error);
  return item;
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
