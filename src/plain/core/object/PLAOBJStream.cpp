#include "plain/core/object/PLAOBJStream.hpp"
#include "plain/core/object/PLAOBJError.hpp"

PLAOBJStream::Manager PLAOBJStream::Manager::_instance = PLAOBJStream::Manager();

PLAOBJStream::PLAOBJStream(const PLAString &aName) :
  GRAOBJBinder<PLAOBJStream>::Item(aName, Manager::Instance())
{

}

PLAOBJStream::~PLAOBJStream()
{

}

void PLAOBJStream::Bind()
{
  GRAOBJBinder<PLAOBJStream>::Error error(GRAOBJBinder<PLAOBJStream>::Error::None);
  PLAOBJStream::Manager::Instance()->Bind(this, &error);
  if (error != GRAOBJBinder<PLAOBJStream>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJStream binding. ERROR : %02d", error); }
}

void PLAOBJStream::Unbind()
{
  GRAOBJBinder<PLAOBJStream>::Error error(GRAOBJBinder<PLAOBJStream>::Error::None);
  PLAOBJStream::Manager::Instance()->Unbind(this, &error);
  if (error != GRAOBJBinder<PLAOBJStream>::Error::None)
  { PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Failed PLAOBJStream unbinding. ERROR : %02d", error); }
}

const PLAString &PLAOBJStream::GetName() const
{
  return this->PLAStreamItem::GetName();
}

const char *PLAOBJStream::GetBinderItemTypeName() const
{
  return "PLAOBJStream";
}

// Manager Implementation //////////////////////////////////////////////////////

PLAOBJStream::Manager::Manager()
{

}

PLAOBJStream::Manager::~Manager()
{
  if (_cameraInputContext)
  {
    delete _cameraInputContext;
    _cameraInputContext = nullptr;
  }
}

void PLAOBJStream::Manager::Init()
{

}

void PLAOBJStream::Manager::Update()
{
  // Call Update() on all streams
  // Note: CameraStream handles threading internally, its Update() is a no-op
  for (auto *item : this->GetItems()) {
    if (item) {
      static_cast<PLAOBJStream *>(item)->Update();
    }
  }
}

PLAOBJStream *PLAOBJStream::Manager::Stream(const PLAString &aKey)
{
  GRAOBJBinder<PLAOBJStream>::Error error(GRAOBJBinder<PLAOBJStream>::Error::None);
  return static_cast<PLAOBJStream *>(
    PLAOBJStream::Manager::Instance()->RefItemWithName(aKey, &error));
}

const PLAOBJStream *PLAOBJStream::Manager::GetStream(const PLAString &aName) const
{
  GRAOBJBinder<PLAOBJStream>::Error error(GRAOBJBinder<PLAOBJStream>::Error::None);
  return static_cast<const PLAOBJStream *>(
    this->RefItemWithName(aName, &error));
}

PLAInputContext *PLAOBJStream::Manager::RefContextWithInput(const PLAInput *aInput) const
{
  // Only handle camera input - other input types are handled by Stage
  if (aInput->GetInputDeviceType() != PLAInputDeviceType::Camera)
  {
    return nullptr;
  }

  // Return camera broadcast context (will be created on first use)
  if (!_cameraInputContext)
  {
    const_cast<Manager *>(this)->_cameraInputContext = new PLAInputContext();
  }

  return _cameraInputContext;
}
