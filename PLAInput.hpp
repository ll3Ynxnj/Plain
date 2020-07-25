#ifndef PLAIN_ENGINE_PLAINPUT_HPP
#define PLAIN_ENGINE_PLAINPUT_HPP

#include "PLAObject.hpp"
#include "PLAInputType.hpp"
#include <queue>

class PLAInput : public PLAObject
{
  PLAInputDevice _device;
  PLAInputCode _code;
  PLAInputState _state;

public:
  static PLAInput *Create(PLAInputDevice aType, PLAInputCode aCode,
                          PLAInputState aState);
  static PLAInputCode GetCodeFromChar(unsigned char aCharacter);

  PLAInput(PLAInputDevice aDevice, PLAInputCode aCode, PLAInputState aState);
  ~PLAInput();

// Manager /////////////////////////////////////////////////////////////////////
public:
  class Manager
  {
    static Manager _instance;

    std::queue<PLAInput *> _inputs;

    Manager();

  public:
    static Manager *GetInstance() { return &_instance; }

    ~Manager();

    void Init();
    void Input(PLAInputDevice aDevice, PLAInputCode aCode, PLAInputState aState);
  };
};

#endif //PLAIN_ENGINE_PLAINPUT_HPP
