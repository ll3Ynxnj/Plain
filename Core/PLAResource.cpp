//
// Created by Kentaro Kawai on 2021/03/17.
//

#include "PLAResource.hpp"
#include "PLAError.hpp"

void PLAResource::Bind(PLAResource *aResource)
{
  GRABinder<PLAResource>::Error error(GRABinder<PLAResource>::Error::None);
  PLAResource::Manager::RefInstance()->Bind(aResource, &error);
  if (error != GRABinder<PLAResource>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAResource binding. ERROR : %02d", error); }
}

PLAResource::PLAResource(const std::string &aName, const std::string &aPath) :
  PLAObject(PLAObjectType::Resource, aName),
  GRABinder<PLAResource>::Item(aName, Manager::RefInstance()),
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

void PLAResource::PrintResource() const {
  GRA_PRINT("%12d | %65s\n", this->GetDataSize(), _path.c_str());
}

// PLAResource::Manager ////////////////////////////////////////////////////////

PLAResource::Manager PLAResource::Manager::_instance = PLAResource::Manager();

PLAResource::Manager::Manager() : GRABinder<PLAResource>() {
  this->LoadResource("sample1.raw");
}

PLAResource::Manager::~Manager() {

}

void PLAResource::Manager::PrintResources() const {
  GRA_PRINT("//-- PLAResource::Manager::PrintResource"
            "s --////////////////////////////////////\n");
  GRA_PRINT("        SIZE |                          "
            "                                    PATH\n");
  GRA_PRINT("-------------|--------------------------"
            "----------------------------------------\n");
  for (GRABinder<PLAResource>::Item *item : this->GetItems())
  { static_cast<const PLAResource *>(item)->PrintResource(); }
  GRA_PRINT("////////////////////////////////////////"
            "////////////////////////////////////////\n");
};

void PLAResource::Manager::LoadResource(const std::string &aName) {
  std::string path = "/Users/ll3ynxnj/Projects/anhr/";
  path.append(aName);
  PLARSCImage *image = PLARSCImage::Create(aName, path, 1024, 1024);
  image->AllocData();
}

//-- PLARSCImage --/////////////////////////////////////////////////////////////

PLARSCImage *PLARSCImage::Create(const std::string &aName,
                                 const std::string &aPath,
                                 size_t aWidth, size_t aHeight) {
  PLARSCImage *image = new PLARSCImage(aName, aPath, aWidth, aHeight);
  {
    PLAObject::Bind(image);
    /*
    GRABinder<PLAObject>::Error error(GRABinder<PLAObject>::Error::None);
    PLAObject::Manager::RefInstance()->Bind(image, &error);
    if (error != GRABinder<PLAObject>::Error::None)
    { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Failed PLAObject binding. ERROR : %02d", error); }
    */
  }
  {
    PLAResource::Bind(image);
    /*
    GRABinder<PLAResource>::Error error(GRABinder<PLAResource>::Error::None);
    PLAResource::Manager::RefInstance()->Bind(image, &error);
    if (error != GRABinder<PLAResource>::Error::None)
    { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Failed PLAResource binding. ERROR : %02d", error); }
    */
  }
  return image;
}

PLARSCImage::PLARSCImage(const std::string &aName, const std::string &aPath,
                         size_t aWidth, size_t aHeight) :
  PLAResource(aName, aPath), _width(aWidth), _height(aHeight) {

}

PLARSCImage::~PLARSCImage() {

}

size_t PLARSCImage::GetDataSize() const {
  return _width * _height * 4;
}
