#ifndef PLAIN_ENGINE_PLAOBJSMILEDETECTOR_HPP
#define PLAIN_ENGINE_PLAOBJSMILEDETECTOR_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/analysis/PLAFace.hpp"
#include "plain/core/PLASmileDetectorType.hpp"
#include "grain/object/GRAOBJBinder.hpp"
#include <opencv2/core.hpp>

// Abstract base class for smile detection
// Analyzes cropped face images and detects smiles
class PLAOBJSmileDetector : public PLAObject,
                            private GRAOBJBinder<PLAOBJSmileDetector>::Item
{
  using Binder = GRAOBJBinder<PLAOBJSmileDetector>;

protected:
  bool _isInitialized = false;
  PLAFloat _threshold = 0.5f;

  PLAOBJSmileDetector(const PLAString &aName);

public:
  using PLASmileDetectorItem = GRAOBJBinder<PLAOBJSmileDetector>::Item;
  using PLASmileDetectorError = GRAOBJBinder<PLAOBJSmileDetector>::Error;

  // Factory method (Renderer pattern)
  static PLAOBJSmileDetector *Create(PLASmileDetectorType aType,
                                      const PLAString &aName = "SmileDetector");
  static PLAOBJSmileDetector *Detector(const PLAString &aName);

  void Bind() override;

protected:
  void Unbind() override;

public:
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

//-- GRAOBJBinder::Item --/////////////////////////////////////////////////////////
private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager: public GRAOBJBinder<PLAOBJSmileDetector>
  {
    static Manager _instance;

    Manager();

  public:
    static Manager *Instance() { return &_instance; };

    ~Manager();

    void Init();
  };
};

#endif // PLAIN_ENGINE_PLAOBJSMILEDETECTOR_HPP
