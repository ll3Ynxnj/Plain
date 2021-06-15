#ifndef PLAIN_ENGINE_PLAINPUTTYPE_HPP
#define PLAIN_ENGINE_PLAINPUTTYPE_HPP

#include "Plain.h"

enum class PLAInputDeviceType : PLAInt
{ Touch, Mouse, Key, kNumberOfItems, None = kPLAIntUndefined };

using PLAInputSignal = bool;

using PLAInputFunctor = PLAInt;
static const PLAInt kPLAInputFunctorUndefined = kPLAIntUndefined;

enum class PLAInputFunctorForTouch : PLAInputFunctor
{
  Press, Release, ReleaseOnOutSide, Drag, DragOver, DragOut,
  kNumberOfItems, None = kPLAIntUndefined,
};

enum class PLAInputFunctorForMouse : PLAInputFunctor
{
  Press, Release, ReleaseOnOutSide, Move, Drag, DragOver, DragOut,
  kNumberOfItems, None = kPLAIntUndefined,
};

enum class PLAInputFunctorForKey : PLAInputFunctor
{
  Press, Release,
  kNumberOfItems, None = kPLAIntUndefined
};

using PLAInputCode = PLAInt;
static const PLAInt kPLAInputCodeUndefined = kPLAIntUndefined;

enum class PLAInputCodeForTouch : PLAInputCode
{
  _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
  kNumberOfItems, None = kPLAIntUndefined,
};

// マウスは何も押さずに画面上を移動させられるため移動時は常にNoneを送出する
// Noneは他のキーが押されていてもいなくても送出されるので、Handler側で処理を分ける
enum class PLAInputCodeForMouse : PLAInputCode
{ Left, Middle, Right, kNumberOfItems, None = kPLAIntUndefined };

enum class PLAInputCodeForKey : PLAInputCode
{
  _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  Esc, Tab, Return, Delete, Space, Shift, Control, Alt, Super,
  kNumberOfItems, None = kPLAIntUndefined,
};

#endif //PLAIN_ENGINE_PLAINPUTTYPE_HPP
