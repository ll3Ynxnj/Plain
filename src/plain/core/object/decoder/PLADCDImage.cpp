// Copyright (c) 2023. CLAYWORK Inc. All rights reserved.

#include "plain/core/object/decoder/PLADCDImage.hpp"
#include "plain/core/object/PLAOBJError.hpp"

#include <cstring>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

PLADCDImage *PLADCDImage::Create(const PLAString &aName)
{
  PLADCDImage *decoder = new PLADCDImage(aName);
  if (!decoder->Initialize()) {
    delete decoder;
    return nullptr;
  }
  return decoder;
}

PLADCDImage::PLADCDImage(const PLAString &aName) :
  PLAOBJDecoder(aName)
{
}

PLADCDImage::~PLADCDImage()
{
}

bool PLADCDImage::Initialize()
{
  _isInitialized = true;
  return true;
}

PLAImageType PLADCDImage::DetectType(const PLAUInt8 *aHeader, size_t aSize)
{
  if (aSize < 8) {
    return PLAImageType::Raw;
  }

  // PNG signature: 89 50 4E 47 0D 0A 1A 0A
  static const PLAUInt8 kPNGSignature[8] = {
    0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A
  };
  if (std::memcmp(aHeader, kPNGSignature, 8) == 0) {
    return PLAImageType::Png;
  }

  // JPEG signature: FF D8 FF
  if (aSize >= 3 &&
      aHeader[0] == 0xFF &&
      aHeader[1] == 0xD8 &&
      aHeader[2] == 0xFF) {
    return PLAImageType::Jpg;
  }

  // Default to RAW
  return PLAImageType::Raw;
}

bool PLADCDImage::Decode(const std::vector<PLAUInt8> &aInput,
                          std::vector<PLAUInt8> &aOutput)
{
  if (!_isInitialized || aInput.empty()) {
    return false;
  }

  PLAImageType type = DetectType(aInput.data(), aInput.size());

  switch (type) {
    case PLAImageType::Png:
      return DecodePNG(aInput, aOutput);
    case PLAImageType::Jpg:
      return DecodeJPEG(aInput, aOutput);
    case PLAImageType::Raw:
    default:
      // RAW: copy as-is (no decoding needed)
      aOutput = aInput;
      return true;
  }
}

bool PLADCDImage::DecodePNG(const std::vector<PLAUInt8> &aInput,
                             std::vector<PLAUInt8> &aOutput)
{
  // Decode PNG using OpenCV
  cv::Mat encoded(1, static_cast<int>(aInput.size()), CV_8UC1,
                  const_cast<PLAUInt8 *>(aInput.data()));
  cv::Mat decoded = cv::imdecode(encoded, cv::IMREAD_UNCHANGED);

  if (decoded.empty()) {
    PLA_ERROR_ISSUE(PLAErrorType::Expect, "Failed to decode PNG image.");
    return false;
  }

  // Convert to RGBA
  cv::Mat rgba;
  if (decoded.channels() == 4) {
    cv::cvtColor(decoded, rgba, cv::COLOR_BGRA2RGBA);
  } else if (decoded.channels() == 3) {
    cv::cvtColor(decoded, rgba, cv::COLOR_BGR2RGBA);
  } else if (decoded.channels() == 1) {
    cv::cvtColor(decoded, rgba, cv::COLOR_GRAY2RGBA);
  } else {
    PLA_ERROR_ISSUE(PLAErrorType::Expect,
                    "Unexpected number of channels: %d", decoded.channels());
    return false;
  }

  _decodedWidth  = static_cast<PLASize>(rgba.cols);
  _decodedHeight = static_cast<PLASize>(rgba.rows);

  // Copy to output vector
  size_t dataSize = rgba.cols * rgba.rows * 4;
  aOutput.resize(dataSize);
  std::memcpy(aOutput.data(), rgba.data, dataSize);

  return true;
}

bool PLADCDImage::DecodeJPEG(const std::vector<PLAUInt8> &aInput,
                              std::vector<PLAUInt8> &aOutput)
{
  // Decode JPEG using OpenCV (same approach as PNG)
  cv::Mat encoded(1, static_cast<int>(aInput.size()), CV_8UC1,
                  const_cast<PLAUInt8 *>(aInput.data()));
  cv::Mat decoded = cv::imdecode(encoded, cv::IMREAD_UNCHANGED);

  if (decoded.empty()) {
    PLA_ERROR_ISSUE(PLAErrorType::Expect, "Failed to decode JPEG image.");
    return false;
  }

  // Convert to RGBA (JPEG doesn't have alpha, but we use RGBA for consistency)
  cv::Mat rgba;
  if (decoded.channels() == 3) {
    cv::cvtColor(decoded, rgba, cv::COLOR_BGR2RGBA);
  } else if (decoded.channels() == 1) {
    cv::cvtColor(decoded, rgba, cv::COLOR_GRAY2RGBA);
  } else {
    PLA_ERROR_ISSUE(PLAErrorType::Expect,
                    "Unexpected number of channels: %d", decoded.channels());
    return false;
  }

  _decodedWidth  = static_cast<PLASize>(rgba.cols);
  _decodedHeight = static_cast<PLASize>(rgba.rows);

  // Copy to output vector
  size_t dataSize = rgba.cols * rgba.rows * 4;
  aOutput.resize(dataSize);
  std::memcpy(aOutput.data(), rgba.data, dataSize);

  return true;
}
