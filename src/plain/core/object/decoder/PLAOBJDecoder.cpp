// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/decoder/PLAOBJDecoder.hpp"
#include "plain/core/object/decoder/PLADCDImage.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJDecoder *PLAOBJDecoder::Create(PLADecoderType aType,
                                      const PLAString &aName)
{
  PLAOBJDecoder *decoder = nullptr;

  switch (aType)
  {
    case PLADecoderType::Image:
      decoder = PLADCDImage::Create(aName);
      break;
    case PLADecoderType::Audio:
      PLA_ERROR_ISSUE(PLAErrorType::Expect,
                      "Audio decoder is not implemented yet.");
      return nullptr;
    default:
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Unexpected decoder type detected.");
      return nullptr;
  }

  if (decoder) {
    decoder->Bind();
  }
  return decoder;
}

PLAOBJDecoder *PLAOBJDecoder::Decoder(const PLAString &aName)
{
  GRAOBJBinder<PLAOBJDecoder>::Error error(GRAOBJBinder<PLAOBJDecoder>::Error::None);
  return static_cast<PLAOBJDecoder *>(Manager::Instance()->RefItemWithName(aName, &error));
}

void PLAOBJDecoder::Bind()
{
  this->PLAObject::Bind();

  GRAOBJBinder<PLAOBJDecoder>::Error error(GRAOBJBinder<PLAOBJDecoder>::Error::None);
  PLAOBJDecoder::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJDecoder>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJDecoder binding. ERROR : %02d", error);
  }
}

void PLAOBJDecoder::Unbind()
{
  GRAOBJBinder<PLAOBJDecoder>::Error error(GRAOBJBinder<PLAOBJDecoder>::Error::None);
  PLAOBJDecoder::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJDecoder>::Error::None)
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJDecoder unbinding. ERROR : %02d", error);
  }

  this->PLAObject::Unbind();
}

PLAOBJDecoder::PLAOBJDecoder(const PLAString &aName) :
  PLAObject(PLAObjectType::Decoder, aName),
  GRAOBJBinder<PLAOBJDecoder>::Item(aName, Manager::Instance())
{
}

PLAOBJDecoder::~PLAOBJDecoder()
{
}

// GRAOBJBinder::Item //////////////////////////////////////////////////////////

const char *PLAOBJDecoder::GetBinderItemTypeName() const
{
  static const char *kName = "PLAOBJDecoder";
  return kName;
}

// PLAOBJDecoder::Manager //////////////////////////////////////////////////////

PLAOBJDecoder::Manager PLAOBJDecoder::Manager::_instance =
  PLAOBJDecoder::Manager();

PLAOBJDecoder::Manager::Manager() : GRAOBJBinder<PLAOBJDecoder>()
{
}

PLAOBJDecoder::Manager::~Manager()
{
}

void PLAOBJDecoder::Manager::Init()
{
  GRAOBJBinder<PLAOBJDecoder>::Init();
}
