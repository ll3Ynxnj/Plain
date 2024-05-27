//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef ANHR_PLAINPUTSTATE_HPP
#define ANHR_PLAINPUTSTATE_HPP

#include "Core/Object/Input/PLAInput.hpp"

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

#endif //ANHR_PLAINPUTSTATE_HPP
