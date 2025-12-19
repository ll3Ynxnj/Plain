#ifndef PLAIN_ENGINE_PLASMILEDETECTORTYPE_HPP
#define PLAIN_ENGINE_PLASMILEDETECTORTYPE_HPP

#include "plain/core/primitive/PLAPRMType.hpp"

enum class PLASmileDetectorType : PLAInt
{
  OpenCVCascade,    // CascadeClassifier (haarcascade_smile.xml)
  CNN,              // CNN-based expression recognition

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif // PLAIN_ENGINE_PLASMILEDETECTORTYPE_HPP
