#include <filesystem>

#include <iostream>
#include <fstream>

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
  std::ifstream file(_path, std::ios::binary | std::ios::ate); // ファイルの終端で開く
  if (!file) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "%s could not be opened.", _path.c_str());
  }

  //-- Get file size
  std::streamsize dataSize = file.tellg();
  file.seekg(0, std::ios::beg); // Restore the file position to the beginning

  //-- Prepare a buffer to read data
  _data.resize(dataSize);

  //-- Read data
  if (file.read(reinterpret_cast<char*>(_data.data()), dataSize)) {
    _size = dataSize;
    GRA_PRINT("Successfully read data.\n");
  } else {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to read data: The file was only partially read.");
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

/*
void PLAOBJResource::Manager::Init()
{
  GRAOBJBinder<PLAOBJResource>::Init();

  this->LoadResource("sample0.raw");
  this->LoadResource("sample1.raw");
  this->LoadResource("tilechip.raw");
  this->LoadResource("font0.raw");
}
 */

void PLAOBJResource::Manager::Init()
{
  GRAOBJBinder<PLAOBJResource>::Init();
  this->Load();
}

void PLAOBJResource::Manager::Load()
{
  std::string path = "Resources";
  for (const auto& entry : std::filesystem::directory_iterator(path))
  {
    if (entry.is_regular_file())
    {
      std::string filename = entry.path().filename().string();
      this->LoadResource(filename);
    }
  }
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
  //PLAString path = "/Users/ll3ynxnj/03_Projects/13_CMake/anhr/Resources/";
  PLAString path = "Resources/";
  path.append(aName);
  PLAOBJResource *resource = PLAOBJResource::Create(aName, path);
  resource->AllocData();
}
