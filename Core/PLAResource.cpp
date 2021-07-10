#include "PLAResource.hpp"
#include "PLAError.hpp"

PLAResource *PLAResource::Create(const std::string &aName, const std::string &aPath)
{
  PLAResource *resource = new PLAResource(aName, aPath);
  PLAObject::Bind(resource);
  PLAResource::Bind(resource);
  return resource;
}

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
  size_t dataSize = this->GetSize();
  _data = new uint8_t[dataSize];
  FILE *fp;

  if ((fp = fopen(_path.c_str(), "rb")) != nullptr) {
    fread(_data, dataSize, 1, fp);
    fclose(fp);
    int result = fread(_data, dataSize, 1, fp);
    GRA_PRINT("result : %d\n", result);
  } else {
    perror(_path.c_str());
  }
}

void PLAResource::ReleaseData() {
  //GRA_DELETE_ARRAY(_data)
}

void PLAResource::PrintResource() const {
  GRA_PRINT("%12d | %65s\n", this->GetSize(), _path.c_str());
}

// PLAResource::Manager ////////////////////////////////////////////////////////

PLAResource::Manager PLAResource::Manager::_instance = PLAResource::Manager();

PLAResource::Manager::Manager() : GRABinder<PLAResource>() {
  this->LoadResource("sample0.raw");
  this->LoadResource("sample1.raw");
  this->LoadResource("sample2.raw");
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
  PLAResource *resource = PLAResource::Create(aName, path);
  resource->AllocData();
}
