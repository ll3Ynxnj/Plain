#include "plain/core/object/input/PLAIPTKey.hpp"

PLAIPTKey::PLAIPTKey(PLAInputSignalCode aCode, PLAInputSignal aSignal):
  PLAInput(PLAInputDeviceType::Keyboard, aCode, aSignal)
{

}

PLAIPTKey::~PLAIPTKey()
{

}
