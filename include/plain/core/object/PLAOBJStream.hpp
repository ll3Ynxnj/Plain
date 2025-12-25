#ifndef PLAIN_PLAOBJSTREAM_HPP
#define PLAIN_PLAOBJSTREAM_HPP

#include "plain/core/object/PLAObject.hpp"
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
//
// Note: Threading is NOT handled by base class.
// Derived classes that need threading (e.g., CameraStream) handle it internally.
class PLAOBJStream : public PLAObject,
                     private GRAOBJBinder<PLAOBJStream>::Item
{
  using Binder = GRAOBJBinder<PLAOBJStream>;
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

  // Flag for consumers to check if stream has been updated
  std::atomic<bool> _isUpdated{false};

public:
  PLAOBJStream(const PLAString &aName);
  virtual ~PLAOBJStream();

  void Bind() override;

protected:
  void Unbind() override;

public:

  // Update the stream (fetch next frame, generate next data, etc.)
  // For synchronous streams: called by Manager::Update()
  // For async streams (e.g., CameraStream): may be no-op if internal thread handles it
  virtual void Update() = 0;

  // Check if stream has been updated (called by consumers)
  bool IsUpdated() const { return _isUpdated; }

  // Mark data as consumed (called by consumers after reading)
  void Consume() { _isUpdated = false; }

  // Get current data for rendering (thread-safe read from front buffer)
  const PLAUInt8 *GetCurrentData() const { return _buffers[_frontIndex].data(); }
  const PLAOBJImageSize &GetSize() const { return _size; }
  PLAImageType GetType() const { return _type; }

  // Check if stream has valid data
  bool IsValid() const { return !_buffers[_frontIndex].empty(); }

protected:
  // Get back buffer for writing new data (not thread-safe, caller must ensure exclusivity)
  std::vector<PLAUInt8> &GetBackBuffer() { return _buffers[1 - _frontIndex]; }

  // Swap buffers atomically (thread-safe)
  void SwapBuffers() {
    std::lock_guard<std::mutex> lock(_swapMutex);
    _frontIndex = 1 - _frontIndex;
    _isUpdated = true;
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
    void Update();  // Update all streams
    const PLAOBJStream *GetStream(const PLAString &aName) const;

    // PLAInputHandler implementation
    PLAInputContext *RefContextWithInput(const PLAInput *aInput) const override;
  };
};

#endif //PLAIN_PLAOBJSTREAM_HPP
