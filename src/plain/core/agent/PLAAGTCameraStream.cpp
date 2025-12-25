#include "plain/core/agent/PLAAGTCameraStream.hpp"
#include "plain/core/object/PLAOBJCameraStream.hpp"

PLAAGTCameraStream::PLAAGTCameraStream(PLAOBJCameraStream *aOwner) :
  PLAAgent(aOwner)
{

}

PLAAGTCameraStream::~PLAAGTCameraStream() noexcept
{

}

bool PLAAGTCameraStream::IsOpened() const
{
  return this->GetCameraStream()->IsOpened();
}

int PLAAGTCameraStream::GetCameraID() const
{
  return this->GetCameraStream()->GetCameraID();
}

bool PLAAGTCameraStream::IsUpdated() const
{
  return this->GetCameraStream()->IsUpdated();
}

void PLAAGTCameraStream::Consume()
{
  this->RefCameraStream()->Consume();
}

PLAOBJFrameSource *PLAAGTCameraStream::GetFrameSource() const
{
  return this->RefCameraStream();
}

const PLAOBJCameraStream *PLAAGTCameraStream::GetCameraStream() const
{
  return static_cast<const PLAOBJCameraStream *>(this->GetOwner());
}

PLAOBJCameraStream *PLAAGTCameraStream::RefCameraStream() const
{
  return static_cast<PLAOBJCameraStream *>(this->RefOwner());
}
