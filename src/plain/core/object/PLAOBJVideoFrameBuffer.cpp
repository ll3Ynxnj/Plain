#include "plain/core/object/PLAOBJVideoFrameBuffer.hpp"
#include <sstream>

PLAId PLAOBJVideoFrameBuffer::_nextBufferId = 0;

PLAOBJVideoFrameBuffer::PLAOBJVideoFrameBuffer()
{
  _bufferId = _nextBufferId++;
}

PLAOBJVideoFrameBuffer::~PLAOBJVideoFrameBuffer()
{
  // Note: PLAOBJImage and PLAOBJResource are managed objects
  // We should not manually delete them here
  // They will be cleaned up by their respective managers
  _image = nullptr;
  _resource = nullptr;
}

void PLAOBJVideoFrameBuffer::UpdateFrame(const cv::Mat &aFrame)
{
  if (aFrame.empty()) { return; }

  // Convert frame size to PLAOBJImageSize
  PLAOBJImageSize frameSize = PLAOBJImageSize(aFrame.cols, aFrame.rows);

  // Convert cv::Mat to RGBA format if needed
  cv::Mat rgbaFrame;
  if (aFrame.channels() == 3)
  {
    cv::cvtColor(aFrame, rgbaFrame, cv::COLOR_BGR2RGBA);
  }
  else if (aFrame.channels() == 4)
  {
    cv::cvtColor(aFrame, rgbaFrame, cv::COLOR_BGRA2RGBA);
  }
  else
  {
    // Unsupported format
    return;
  }

  PLASize dataSize = frameSize.x * frameSize.y * 4; // RGBA 4 bytes per pixel

  // If size changed, recreate resource and image
  if (_size != frameSize || !_resource || !_image)
  {
    // Note: Old objects are managed by their managers
    // Just create new ones - the old ones will remain in the manager
    // TODO: Consider if we need to clean up old resources to prevent memory leaks

    // Create unique names using buffer ID
    std::stringstream resourceName, imageName;
    resourceName << "video_frame_resource_" << _bufferId;
    imageName << "video_frame_" << _bufferId;

    // Create new resource from memory
    _resource = PLAOBJResource::CreateFromMemory(resourceName.str().c_str(),
                                                 rgbaFrame.data, dataSize);

    // Create new image using the resource we just created (NOT CreateFromMemory!)
    _image = new PLAOBJImage(imageName.str().c_str(), _resource, frameSize, PLAImageType::Raw);
    _image->Bind();

    _size = frameSize;
    _type = PLAImageType::Raw;
  }
  else
  {
    // Update existing resource data
    _resource->UpdateData(rgbaFrame.data, dataSize);
  }
}

void PLAOBJVideoFrameBuffer::UpdateFrameFromRGBA(const PLAUInt8 *aData,
                                                   const PLAOBJImageSize &aSize,
                                                   PLASize aDataSize)
{
  if (!aData || aDataSize == 0) { return; }

  // If size changed, recreate resource and image
  if (_size != aSize || !_resource || !_image)
  {
    // Create unique names using buffer ID
    std::stringstream resourceName, imageName;
    resourceName << "video_frame_resource_" << _bufferId;
    imageName << "video_frame_" << _bufferId;

    // Create new resource from memory
    _resource = PLAOBJResource::CreateFromMemory(resourceName.str().c_str(),
                                                 aData, aDataSize);

    // Create new image using the resource we just created (NOT CreateFromMemory!)
    _image = new PLAOBJImage(imageName.str().c_str(), _resource, aSize, PLAImageType::Raw);
    _image->Bind();

    _size = aSize;
    _type = PLAImageType::Raw;
  }
  else
  {
    // Update existing resource data directly from stream
    _resource->UpdateData(aData, aDataSize);
  }
}
