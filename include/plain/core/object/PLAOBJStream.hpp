#ifndef PLAIN_PLAOBJSTREAM_HPP
#define PLAIN_PLAOBJSTREAM_HPP

#include "plain/core/object/PLAOBJImage.hpp"
#include "grain/object/GRAOBJBinder.hpp"
#include "plain/core/object/input/PLAInputHandler.hpp"
#include <vector>
#include <mutex>
#include <atomic>

// Forward declaration
class PLAOBJStream;

// PLAOBJStream: Base class for dynamic data sources
// Unlike PLAOBJResource (static, immutable assets), Stream represents
// data that changes over time (camera, video file, network, procedural generation)
//
// Philosophy: Following Unix principle of treating everything as a stream
// - Static file: Read once, no updates needed
// - Dynamic source: Continuous flow of data
class PLAOBJStream : private GRAOBJBinder<PLAOBJStream>::Item
{
public:
  using PLAStreamItem = GRAOBJBinder<PLAOBJStream>::Item;
  using PLAStreamError = GRAOBJBinder<PLAOBJStream>::Error;

protected:
  // Double buffering for thread-safe access
  std::vector<PLAUInt8> _buffers[2];  // [0] = front (read), [1] = back (write)
  std::atomic<int> _frontIndex{0};
  std::mutex _swapMutex;

  PLAOBJImageSize _size = kPLAOBJImageSizeNone;
  PLAImageType _type = PLAImageType::None;

public:
  PLAOBJStream(const PLAString &aName);
  virtual ~PLAOBJStream();

  void Bind();
  void Unbind();

  // Update the stream (fetch next frame, generate next data, etc.)
  // Must be implemented by derived classes
  virtual void Update() = 0;

  // Get current data for rendering (thread-safe read from front buffer)
  const PLAUInt8 *GetCurrentData() const { return _buffers[_frontIndex].data(); }
  const PLAOBJImageSize &GetSize() const { return _size; }
  PLAImageType GetType() const { return _type; }

  // Check if stream has valid data
  bool IsValid() const { return !_buffers[_frontIndex].empty(); }

protected:
  // Get back buffer for writing new data (not thread-safe, caller must ensure exclusivity)
  std::vector<PLAUInt8> &GetBackBuffer() { return _buffers[1 - _frontIndex]; }

  // Swap buffers after writing new data (thread-safe)
  void SwapBuffers() {
    std::lock_guard<std::mutex> lock(_swapMutex);
    _frontIndex = 1 - _frontIndex;
  }

  const PLAString &GetName() const;

private:
  const char *GetBinderItemTypeName() const override;

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager : public GRAOBJBinder<PLAOBJStream>, public PLAInputHandler
  {
    static Manager _instance;
    PLAInputContext *_cameraInputContext = nullptr;  // Broadcasts camera input to all streams

    Manager();

  public:
    static Manager *Instance() { return &_instance; }
    static PLAOBJStream *Stream(const PLAString &aKey);

    ~Manager();

    void Init();
    const PLAOBJStream *GetStream(const PLAString &aName) const;

    // PLAInputHandler implementation
    PLAInputContext *RefContextWithInput(const PLAInput *aInput) const override;
  };
};

#endif //PLAIN_PLAOBJSTREAM_HPP
