#include <filesystem>

#include <iostream>
#include <fstream>

#include "plain/core/object/PLAOBJResource.hpp"
#include "plain/core/object/PLAOBJError.hpp"
#include "plain/core/object/decoder/PLADCDImage.hpp"

PLAOBJResource *PLAOBJResource::Create(const PLAString &aName, const PLAString &aPath)
{
  PLAOBJResource *resource = new PLAOBJResource(aName, aPath);
  resource->Bind();
  return resource;
}

PLAOBJResource *PLAOBJResource::CreateFromMemory(const PLAString &aName, const PLAUInt8 *aData, PLASize aSize)
{
  PLAOBJResource *resource = new PLAOBJResource(aName, "");
  resource->_data.assign(aData, aData + aSize);
  resource->_size = aSize;
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
  std::ifstream file(_path, std::ios::binary | std::ios::ate);
  if (!file) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "%s could not be opened.", _path.c_str());
    return;
  }

  //-- Get file size
  std::streamsize dataSize = file.tellg();
  file.seekg(0, std::ios::beg);

  //-- Read raw file data
  std::vector<PLAUInt8> rawData(dataSize);
  if (!file.read(reinterpret_cast<char*>(rawData.data()), dataSize)) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed to read data: The file was only partially read.");
    return;
  }

  //-- Detect image type using magic bytes
  _imageType = PLADCDImage::DetectType(rawData.data(), rawData.size());

  if (_imageType == PLAImageType::Png || _imageType == PLAImageType::Jpg) {
    //-- Decode image using PLADCDImage
    PLADCDImage *decoder = PLADCDImage::Create("ResourceDecoder");
    if (!decoder) {
      PLA_ERROR_ISSUE(PLAErrorType::Expect,
                      "Failed to create image decoder for: %s", _path.c_str());
      _data = std::move(rawData);
      _size = _data.size();
      return;
    }

    std::vector<PLAUInt8> decodedData;
    if (decoder->Decode(rawData, decodedData)) {
      _data        = std::move(decodedData);
      _size        = _data.size();
      _imageWidth  = decoder->GetDecodedWidth();
      _imageHeight = decoder->GetDecodedHeight();
      GRA_DEBUG("Successfully decoded %s (%dx%d, %zu bytes)",
                _path.c_str(), _imageWidth, _imageHeight, _size);
    } else {
      PLA_ERROR_ISSUE(PLAErrorType::Expect,
                      "Failed to decode image: %s", _path.c_str());
      _data = std::move(rawData);
      _size = _data.size();
    }

    delete decoder;
  } else {
    //-- RAW or unknown format: use data as-is
    _data = std::move(rawData);
    _size = _data.size();
    GRA_DEBUG("Successfully read data from %s (%zu bytes)", _path.c_str(), _size);
  }
}

void PLAOBJResource::ReleaseData()
{
  // TODO: 動的リソース読込/解放の実装時に以下を追加
  //
  // - Resourceデータ解放時、対応するテクスチャキャッシュも破棄
  // - PLAFunctionCode::Resource::OnRelease コールバックで開放を通知
  // - 継承先クラス（Image, Video等）でRelease通知をパススルー
  //
  // 現状は静的リソースのみのため、この処理は不要。

  // TODO: Implement dynamic resource loading/unloading
  //
  // - When releasing resource data, also discard the corresponding texture cache
  // - Notify release via PLAFunctionCode::Resource::OnRelease callback
  // - Pass through release notification in derived classes (Image, Video, etc.)
  //
  // Currently, only static resources are used, so this process is unnecessary.

  //GRA_DELETE_ARRAY(_data)
}

const char *PLAOBJResource::GetResourceTypeName() const
{
  static const char *kName = "== STUB ==";
  return kName;
}

void PLAOBJResource::UpdateData(const PLAUInt8 *aData, PLASize aSize)
{
  if (aSize != _size) {
    _data.resize(aSize);
    _size = aSize;
  }
  std::copy(aData, aData + aSize, _data.begin());
}

void PLAOBJResource::PrintResource() const
{
  GRA_DEBUG("%12d | %65s", this->GetSize(), _path.c_str());
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
  GRA_DEBUG("//-- PLAOBJResource::Manager::PrintResource"
            "s --////////////////////////////////////\n");
  GRA_DEBUG("        SIZE |                          "
            "                                    PATH\n");
  GRA_DEBUG("-------------|--------------------------"
            "----------------------------------------\n");
  for (GRAOBJBinder<PLAOBJResource>::Item *item : this->GetItems())
  { static_cast<const PLAOBJResource *>(item)->PrintResource(); }
  GRA_DEBUG("////////////////////////////////////////"
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
