//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef PLAIN_PLAINPUTSTATE_HPP
#define PLAIN_PLAINPUTSTATE_HPP

//#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/object/input/PLAIPTTouch.hpp"
#include "plain/core/object/input/PLAIPTMouse.hpp"
#include "plain/core/object/input/PLAIPTKey.hpp"
#include "plain/core/object/input/PLAIPTCamera.hpp"

class PLAInputState
{
  /*std::vector<std::vector<const PLAInput *>> _inputs = {};*/
  std::vector<PLAIPTTouch> _touches;
  std::vector<PLAIPTMouse> _mouses;
  std::vector<PLAIPTKey> _keys;
  std::vector<PLAIPTCamera> _cameras;

public:
  PLAInputState();
  ~PLAInputState();

  const PLAInput *GetInput(const PLAInput &aInput) const;
  const PLAInput *GetInput(PLAInputDeviceType aDevice, PLAInputSignalCode aCode) const;

  void SetInput(const PLAInput *aInput);
};

#endif //PLAIN_PLAINPUTSTATE_HPP
