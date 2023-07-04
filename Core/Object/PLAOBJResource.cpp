#include "PLAOBJResource.hpp"
#include "PLAOBJError.hpp"

PLAOBJResource *PLAOBJResource::Create(const PLAString &aName, const PLAString &aPath)
{
  PLAOBJResource *resource = new PLAOBJResource(aName, aPath);
  resource->Bind();
  return resource;
}

void PLAOBJResource::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJResource>::Error error(GRAOBJBinder<PLAOBJResource>::Error::None);
  PLAOBJResource::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJResource>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJResource binding. ERROR : %02d", error); }
}

void PLAOBJResource::Unbind()
{
  GRAOBJBinder<PLAOBJResource>::Error error(GRAOBJBinder<PLAOBJResource>::Error::None);
  PLAOBJResource::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJResource>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJResource unbinding. ERROR : %02d", error); }

  this->PLAObject::Unbind();
}

PLAOBJResource::PLAOBJResource(const PLAString &aName, const PLAString &aPath) :
  PLAObject(PLAObjectType::Resource, aName),
  GRAOBJBinder<PLAOBJResource>::Item(aName, Manager::Instance()),
  _path(aPath)
{

}

PLAOBJResource::~PLAOBJResource() noexcept
{

}

void PLAOBJResource::AllocData()
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

void PLAOBJResource::ReleaseData()
{
  //GRA_DELETE_ARRAY(_data)
}

const char *PLAOBJResource::GetResourceTypeName() const
{
  static const char *kName = "== STUB ==";
  return kName;
}

void PLAOBJResource::PrintResource() const
{
  GRA_PRINT("%12d | %65s\n", this->GetSize(), _path.c_str());
}

// GRAOBJBinder::Item /////////////////////////////////////////////////////////////

const char *PLAOBJResource::GetBinderItemTypeName() const
{
  return this->GetResourceTypeName();
}

// PLAOBJResource::Manager ////////////////////////////////////////////////////////

PLAOBJResource::Manager PLAOBJResource::Manager::_instance = PLAOBJResource::Manager();

PLAOBJResource::Manager::Manager() : GRAOBJBinder<PLAOBJResource>()
{

}

PLAOBJResource::Manager::~Manager()
{

}

void PLAOBJResource::Manager::Init()
{
  GRAOBJBinder<PLAOBJResource>::Init();

  this->LoadResource("sample0.raw");
  this->LoadResource("sample1.raw");
  this->LoadResource("sample2.raw");
  this->LoadResource("font0.raw");
}

PLAOBJResource *PLAOBJResource::Manager::Resource(const PLAString &aKey)
{
  GRAOBJBinder<PLAOBJResource>::Error error(GRAOBJBinder<PLAOBJResource>::Error::None);
  return static_cast<PLAOBJResource *>(_instance.RefItemWithName(aKey, &error));
}

void PLAOBJResource::Manager::PrintResources() const
{
  GRA_PRINT("//-- PLAOBJResource::Manager::PrintResource"
            "s --////////////////////////////////////\n");
  GRA_PRINT("        SIZE |                          "
            "                                    PATH\n");
  GRA_PRINT("-------------|--------------------------"
            "----------------------------------------\n");
  for (GRAOBJBinder<PLAOBJResource>::Item *item : this->GetItems())
  { static_cast<const PLAOBJResource *>(item)->PrintResource(); }
  GRA_PRINT("////////////////////////////////////////"
            "////////////////////////////////////////\n");
};

const PLAOBJResource *PLAOBJResource::Manager::GetResource(const PLAString &aName) const
{
  PLAResourceError error = PLAResourceError::None;
  const PLAOBJResource *resource =
    static_cast<const PLAOBJResource *>(this->GetItemWithName(aName, &error));
  if (error != PLAResourceError::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to get resource. ERROR : %02d", error);
  }
  return resource;
};

void PLAOBJResource::Manager::LoadResource(const PLAString &aName)
{
  PLAString path = "/Users/ll3ynxnj/Projects/anhr/";
  path.append(aName);
  PLAOBJResource *resource = PLAOBJResource::Create(aName, path);
  resource->AllocData();
}
