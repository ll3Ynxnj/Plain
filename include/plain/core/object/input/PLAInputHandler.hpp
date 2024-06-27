//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef PLAIN_PLAINPUTHANDLER_HPP
#define PLAIN_PLAINPUTHANDLER_HPP

#include "plain/core/object/input/PLAInput.hpp"
#include "plain/core/object/input/PLAInputContext.hpp"
#include "plain/core/object/input/PLAInputState.hpp"

class PLAInputHandler
{
  /// \~ja 入力の対象は常に一つ
  PLAInputContext *_context = nullptr;

public:
  PLAInputHandler();
  ~PLAInputHandler();

  void Input(const PLAInput &aInput, const PLAInputState *aState);
  virtual PLAInputContext *RefContextWithInput(const PLAInput &aInput) const = 0;
  const PLAInputContext *GetContextWithInput(const PLAInput &aInput) const
  { return this->RefContextWithInput(aInput); }

private:
  void InputForTouch(const PLAInput &aInput, const PLAInputState *aState);
  void InputForMouse(const PLAInput &aInput, const PLAInputState *aState);
  void InputForKeyboard(const PLAInput &aInput, const PLAInputState *aState);
  void InputForCamera(const PLAInput &aInput, const PLAInputState *aState);
};

#endif //PLAIN_PLAINPUTHANDLER_HPP
