#ifndef PLAIN_PLAAGTCAMERASTREAM_HPP
#define PLAIN_PLAAGTCAMERASTREAM_HPP

#include "plain/core/agent/PLAAgent.hpp"

class PLAOBJCameraStream;
class PLAOBJFrameSource;

class PLAAGTCameraStream : public PLAAgent
{
public:
  PLAAGTCameraStream() = delete;
  explicit PLAAGTCameraStream(PLAOBJCameraStream *aOwner);
  virtual ~PLAAGTCameraStream() noexcept;

  bool IsOpened() const;
  int GetCameraID() const;
  bool IsUpdated() const;
  void Consume();

  PLAOBJFrameSource *GetFrameSource() const;

private:
  const PLAOBJCameraStream *GetCameraStream() const;
  PLAOBJCameraStream *RefCameraStream() const;
};

#endif //PLAIN_PLAAGTCAMERASTREAM_HPP
