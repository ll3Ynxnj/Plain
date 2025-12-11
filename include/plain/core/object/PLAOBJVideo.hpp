//
// Created by ll3ynxnj on 6/19/24.
//

#ifndef SMIRALJETSON_PLAOBJVIDEO_HPP
#define SMIRALJETSON_PLAOBJVIDEO_HPP

#include "plain/core/object/PLAObject.hpp"
#include "plain/core/object/PLAOBJStream.hpp"
#include "plain/core/object/PLAOBJImage.hpp"

// PLAOBJVideo provides dynamic image access from streams
// - References a Stream (camera, file, network, etc.) - does NOT own it
// - Directly accesses stream data without additional buffering
// - Provides GetCurrentImage() for VideoClip rendering
//
// Design: Exactly mirrors PLAOBJImage/PLAOBJResource relationship
// - PLAOBJVideo references PLAOBJStream (managed by PLAOBJStream::Manager)
// - PLAOBJVideo is a thin wrapper for dynamic image access
// - Stream update is caller's responsibility (like Resource loading)
class PLAOBJVideo : public PLAObject
{
private:
  PLAOBJStream *_stream = nullptr;  // Referenced stream (NOT owned)
  PLAOBJImage *_image = nullptr;     // Temporary image wrapper

public:
  static PLAOBJVideo *Create(const PLAString &aStreamName);

public:
  PLAOBJVideo(const PLAString &aName, PLAOBJStream *aStream);
  ~PLAOBJVideo();

  // Get current frame as image (for VideoClip rendering)
  // Wraps current stream data as PLAOBJImage
  const PLAOBJImage *GetCurrentImage();

  // Get referenced stream
  PLAOBJStream *GetStream() const { return _stream; }
};

#endif //SMIRALJETSON_PLAOBJVIDEO_HPP
