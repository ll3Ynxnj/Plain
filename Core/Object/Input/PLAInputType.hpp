#ifndef PLAIN_ENGINE_PLAINPUTTYPE_HPP
#define PLAIN_ENGINE_PLAINPUTTYPE_HPP

#include "Primitive/PLAVector.hpp"

enum class PLAInputDeviceType : PLAInt
{ Touch, Mouse, Keyboard, kNumberOfItems, None = kPLAIntUndefined };

using PLAInputSignal = bool;

using PLAInputActionCode = PLAInt;
static const PLAInt kPLAInputActionCodeUndefined = kPLAIntUndefined;

enum class PLAInputActionCodeForTouch : PLAInputActionCode
{
  Press, Release, ReleaseOnOutSide, Drag, DragOver, DragOut,
  kNumberOfItems, None = kPLAInputActionCodeUndefined,
};

enum class PLAInputActionCodeForMouse : PLAInputActionCode
{
  Press, Release, ReleaseOnOutSide, Roll, RollOver, RollOut, Drag, DragOver, DragOut,
  kNumberOfItems, None = kPLAInputActionCodeUndefined,
};

enum class PLAInputActionCodeForKeyboard : PLAInputActionCode
{
  Press, Release,
  kNumberOfItems, None = kPLAInputActionCodeUndefined
};

using PLAInputSignalCode = PLAInt;
static const PLAInt kPLAInputSignalCodeUndefined = kPLAIntUndefined;

enum class PLAInputSignalCodeForTouch : PLAInputSignalCode
{
  _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
  kNumberOfItems, None = kPLAInputSignalCodeUndefined,
};

// マウスは何も押さずに画面上を移動させられるため移動時は常にNoneを送出する
// Noneは他のキーが押されていてもいなくても送出されるので、Handler側で処理を分ける
enum class PLAInputSignalCodeForMouse : PLAInputSignalCode
{ Left, Middle, Right, kNumberOfItems, None = kPLAInputSignalCodeUndefined };

enum class PLAInputSignalCodeForKeyboard : PLAInputSignalCode
{
  _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  Esc, Tab, Return, Delete, Space, Shift, Control, Alt, Super,
  kNumberOfItems, None = kPLAInputSignalCodeUndefined,
};

#endif //PLAIN_ENGINE_PLAINPUTTYPE_HPP
