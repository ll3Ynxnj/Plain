#ifndef PLAIN_PLAIPTKEY_HPP
#define PLAIN_PLAIPTKEY_HPP

#include "plain/core/object/input/PLAInput.hpp"

class PLAIPTKey: public PLAInput
{
public:
  PLAIPTKey(PLAInputSignalCode aCode, PLAInputSignal aSignal);
  ~PLAIPTKey();
};

#endif //PLAIN_PLAIPTKEY_HPP
