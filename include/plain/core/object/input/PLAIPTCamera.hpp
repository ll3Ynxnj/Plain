#ifndef PLAIN_PLAIPTCAMERA_HPP
#define PLAIN_PLAIPTCAMERA_HPP

#include "plain/core/object/input/PLAInput.hpp"

class PLAIPTCamera: public PLAInput
{
public:
  PLAIPTCamera(PLAInputSignalCode aCode, PLAInputSignal aSignal);
  ~PLAIPTCamera();
};

#endif //PLAIN_PLAIPTCAMERA_HPP
