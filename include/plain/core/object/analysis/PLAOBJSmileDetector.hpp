#ifndef PLAIN_ENGINE_PLAOBJSMILEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOBJSMILEDETECTOR_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "plain/core/PLASmileDetectorType.hpp"
#include <opencv2/core.hpp>

// Abstract base class for smile detection
// Analyzes cropped face images and detects smiles
class PLAOBJSmileDetector : public PLAObject
{
protected:
  bool _isInitialized = false;
  PLAFloat _threshold = 0.5f;

public:
  // Factory method (Renderer pattern)
  static PLAOBJSmileDetector *Create(PLASmileDetectorType aType);

  PLAOBJSmileDetector();
  virtual ~PLAOBJSmileDetector();

  // Initialize the detector
  virtual bool Initialize() = 0;

  // Detect smile in a cropped face image
  // Returns true if detection was performed, updates aFace with smile data
  virtual bool Detect(const cv::Mat &aFaceImage, PLAFace &aFace) = 0;

  // Check if initialized
  bool IsInitialized() const { return _isInitialized; }

  // Threshold for smile classification
  void SetThreshold(PLAFloat aThreshold);
  PLAFloat GetThreshold() const { return _threshold; }
};

#endif // PLAIN_ENGINE_PLAOBJSMILEDETECTOR_HPP
