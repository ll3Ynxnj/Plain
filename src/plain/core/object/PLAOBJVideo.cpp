#include "plain/core/object/PLAOBJVideo.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJVideo *PLAOBJVideo::Create(const PLAString &aStreamName)
{
  // Get existing stream from Stream::Manager
  PLAOBJStream *stream = PLAOBJStream::Manager::Stream(aStreamName);

  if (!stream) {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Stream '%s' not found", aStreamName.c_str());
    return nullptr;
  }

  // Create PLAOBJVideo referencing the stream
  // Use distinct name to avoid conflict with Stream in PLAObject::Manager
  PLAString videoName = aStreamName + "_video";
  PLAOBJVideo *video = new PLAOBJVideo(videoName, stream);
  video->Bind();
  return video;
}

PLAOBJVideo::PLAOBJVideo(const PLAString &aName, PLAOBJStream *aStream) :
  PLAObject(PLAObjectType::Video, aName),
  _stream(aStream)
{
  // No initialization needed - image is created on demand
}

PLAOBJVideo::~PLAOBJVideo()
{
  // Clean up temporary image if it exists
  if (_image) {
    _image->Unbind();
    delete _image;
    _image = nullptr;
  }
  // Note: _stream is NOT deleted here - it's managed by PLAOBJStream::Manager
}

const PLAOBJImage *PLAOBJVideo::GetCurrentImage()
{
  if (!_stream || !_stream->IsValid()) {
    return nullptr;
  }

  // Get current stream data
  const PLAUInt8 *data = _stream->GetCurrentData();
  const PLAOBJImageSize &size = _stream->GetSize();
  PLAImageType type = _stream->GetType();

  // Create or update temporary image wrapper
  // Similar to how PLAOBJImage wraps PLAOBJResource
  if (!_image) {
    // Create image from memory (this creates an internal resource)
    PLAString imageName = this->GetObjectName() + "_frame";
    _image = PLAOBJImage::CreateFromMemory(imageName, data, size, type);
  } else {
    // Update existing image's resource data
    PLASize dataSize = size.x * size.y * 4; // RGBA 4 bytes per pixel
    PLAString resourceName = this->GetObjectName() + "_frame_resource";
    const_cast<PLAOBJResource*>(
      PLAOBJResource::Manager::Instance()->GetResource(resourceName)
    )->UpdateData(data, dataSize);
  }

  return _image;
}
