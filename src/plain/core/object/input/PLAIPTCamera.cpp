#include "plain/core/object/input/PLAIPTCamera.hpp"

PLAIPTCamera::PLAIPTCamera(PLAInputSignalCode aCode, PLAInputSignal aSignal):
  PLAInput(PLAInputDeviceType::Camera, aCode, aSignal)
{

}

PLAIPTCamera::~PLAIPTCamera()
{

}
