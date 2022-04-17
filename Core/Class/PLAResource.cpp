#include "PLAResource.hpp"
#include "PLAError.hpp"

PLAResource *PLAResource::Create(const PLAString &aName, const PLAString &aPath)
{
  PLAResource *resource = new PLAResource(aName, aPath);
  resource->Bind();
  return resource;
}

void PLAResource::Bind()
{
  this->PLAObject::Bind();

  GRABinder<PLAResource>::Error error(GRABinder<PLAResource>::Error::None);
  PLAResource::Manager::Instance()->Bind(this, &error);
  if (error != GRABinder<PLAResource>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAResource binding. ERROR : %02d", error); }
}

void PLAResource::Unbind()
{
  GRABinder<PLAResource>::Error error(GRABinder<PLAResource>::Error::None);
  PLAResource::Manager::Instance()->Unbind(this, &error);
  if (error != GRABinder<PLAResource>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAResource unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAResource::PLAResource(const PLAString &aName, const PLAString &aPath) :
  PLAObject(PLAObjectType::Resource, aName),
  GRABinder<PLAResource>::Item(aName, Manager::Instance()),
  _path(aPath)
{

}

PLAResource::~PLAResource() noexcept
{

}

void PLAResource::AllocData()
{
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

void PLAResource::ReleaseData()
{
  //GRA_DELETE_ARRAY(_data)
}

const char *PLAResource::GetResourceTypeName() const
{
  static const char *kName = "== STUB ==";
  return kName;
}

void PLAResource::PrintResource() const
{
  GRA_PRINT("%12d | %65s\n", this->GetSize(), _path.c_str());
}

// GRABinder::Item /////////////////////////////////////////////////////////////

const char *PLAResource::GetBinderItemTypeName() const
{
  return this->GetResourceTypeName();
}

// PLAResource::Manager ////////////////////////////////////////////////////////

PLAResource::Manager PLAResource::Manager::_instance = PLAResource::Manager();

PLAResource::Manager::Manager() : GRABinder<PLAResource>()
{
  this->LoadResource("sample0.raw");
  this->LoadResource("sample1.raw");
  this->LoadResource("sample2.raw");
}

PLAResource::Manager::~Manager()
{

}

PLAResource *PLAResource::Manager::Resource(const PLAString &aKey)
{
  GRABinder<PLAResource>::Error error(GRABinder<PLAResource>::Error::None);
  return static_cast<PLAResource *>(_instance.RefItem(aKey, &error));
}

void PLAResource::Manager::PrintResources() const
{
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

const PLAResource *PLAResource::Manager::GetResource(const PLAString &aName) const
{
  PLAResourceError error = PLAResourceError::None;
  const PLAResource *resource =
    static_cast<const PLAResource *>(this->GetItem(aName, &error));
  if (error != PLAResourceError::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to get resource. ERROR : %02d", error);
  }
  return resource;
};

void PLAResource::Manager::LoadResource(const PLAString &aName)
{
  PLAString path = "/Users/ll3ynxnj/Projects/anhr/";
  path.append(aName);
  PLAResource *resource = PLAResource::Create(aName, path);
  resource->AllocData();
}
