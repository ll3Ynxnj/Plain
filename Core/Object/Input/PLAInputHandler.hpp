//
// Created by Kentaro Kawai on 2022/05/13.
//

#ifndef ANHR_PLAINPUTHANDLER_HPP
#define ANHR_PLAINPUTHANDLER_HPP

#include "PLAInput.hpp"
#include "PLAInputContext.hpp"
#include "PLAInputState.hpp"

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
};

#endif //ANHR_PLAINPUTHANDLER_HPP
