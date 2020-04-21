#include "PLAErrorManager.hpp"
#include "PLAStage.hpp"

PLAErrorManager PLAErrorManager::_instance = PLAErrorManager();

PLAErrorManager::PLAErrorManager()
{

}

PLAErrorManager::~PLAErrorManager()
{

}

void PLAErrorManager::Init()
{

}

void PLAErrorManager::Reset()
{
  _instance = PLAErrorManager();
}

void PLAErrorManager::Throw(PLAErrorType aType, const std::string &aMessage)
{
  try
  {
    PLAError *error = new PLAError(aType, aMessage);
    _errors.push(error);
    throw error;
  }
  catch (PLAError *aError)
  {
    switch (aError->GetType())
    {
      case PLAErrorType::Assert :
        PLADebug::Assert(aMessage.c_str());
        break;
      default :
        break;
    }
  }
}
