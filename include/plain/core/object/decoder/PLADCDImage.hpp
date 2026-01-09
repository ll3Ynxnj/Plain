// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#ifndef PLAIN_ENGINE_PLADCDIMAGE_HPP
#define PLAIN_ENGINE_PLADCDIMAGE_HPP

#include "plain/core/object/decoder/PLAOBJDecoder.hpp"
#include "plain/core/PLAImageType.hpp"
#include "plain/core/primitive/PLAPRMVector.hpp"

class PLADCDImage : public PLAOBJDecoder
{
  PLASize _decodedWidth  = 0;
  PLASize _decodedHeight = 0;

protected:
  PLADCDImage(const PLAString &aName);

public:
  static PLADCDImage *Create(const PLAString &aName = "ImageDecoder");

  virtual ~PLADCDImage();

  bool Initialize() override;
  bool Decode(const std::vector<PLAUInt8> &aInput,
              std::vector<PLAUInt8> &aOutput) override;

  static PLAImageType DetectType(const PLAUInt8 *aHeader, size_t aSize);

  PLASize GetDecodedWidth() const { return _decodedWidth; }
  PLASize GetDecodedHeight() const { return _decodedHeight; }

private:
  bool DecodePNG(const std::vector<PLAUInt8> &aInput,
                 std::vector<PLAUInt8> &aOutput);
  bool DecodeJPEG(const std::vector<PLAUInt8> &aInput,
                  std::vector<PLAUInt8> &aOutput);
};

#endif // PLAIN_ENGINE_PLADCDIMAGE_HPP
