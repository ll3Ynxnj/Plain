//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef PLAIN_PLAINPUTSTATE_HPP
#define PLAIN_PLAINPUTSTATE_HPP

#include "plain/core/object/input/PLAInput.hpp"

class PLAInputState
{
  std::vector<std::vector<PLAInput>> _inputs = {};

public:
  PLAInputState();
  ~PLAInputState();

  PLAInput GetInput(const PLAInput &aInput) const;
  PLAInput GetInput(PLAInputDeviceType aDevice, PLAInputSignalCode aCode) const;
  void SetInput(const PLAInput &aInput);
};

#endif //PLAIN_PLAINPUTSTATE_HPP
