#ifndef PLAIN_PLAOBJVIDEOFRAMEBUFFER_HPP
#define PLAIN_PLAOBJVIDEOFRAMEBUFFER_HPP

#include "plain/core/object/PLAOBJImage.hpp"
#include "plain/core/object/PLAOBJResource.hpp"
#include <opencv2/opencv.hpp>

// PLAOBJVideoFrameBuffer manages a dynamic frame buffer for video capture
// Unlike PLAOBJImage which is immutable, this buffer can be updated each frame
// It converts cv::Mat frames to PLAOBJImage format for rendering
//
// TODO: This class misuses ResourceManager for dynamic data
// Should be refactored to use Stream-based architecture directly
class PLAOBJVideoFrameBuffer
{
  PLAOBJResource *_resource = nullptr;
  PLAOBJImage *_image = nullptr;
  PLAOBJImageSize _size = kPLAOBJImageSizeNone;
  PLAImageType _type = PLAImageType::None;
  PLAId _bufferId;  // Unique ID for this buffer instance

  static PLAId _nextBufferId;  // Static counter for unique IDs

public:
  PLAOBJVideoFrameBuffer();
  ~PLAOBJVideoFrameBuffer();

  // Update the buffer with a new frame from cv::Mat
  void UpdateFrame(const cv::Mat &aFrame);

  // Update the buffer directly from RGBA data (more efficient for Stream data)
  void UpdateFrameFromRGBA(const PLAUInt8 *aData, const PLAOBJImageSize &aSize, PLASize aDataSize);

  // Get the current image for rendering
  const PLAOBJImage *GetImage() const { return _image; }

  // Check if buffer has valid data
  bool IsValid() const { return _image != nullptr; }
};

#endif //PLAIN_PLAOBJVIDEOFRAMEBUFFER_HPP
