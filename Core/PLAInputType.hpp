#ifndef PLAIN_ENGINE_PLAINPUTTYPE_HPP
#define PLAIN_ENGINE_PLAINPUTTYPE_HPP

//#include "PLAType.hpp"

enum class PLAInputDeviceType : GRAInt
{ Touch, Mouse, Key, kNumberOfItems, None = kGRAIntUndefined };

using PLAInputSignal = bool;

using PLAInputFunctor = GRAInt;
static const GRAInt kPLAInputFunctorUndefined = kGRAIntUndefined;

enum class PLAInputFunctorForTouch : PLAInputFunctor
{
  Press, Release, ReleaseOnOutSide, Drag, DragOver, DragOut,
  kNumberOfItems, None = kGRAIntUndefined,
};

enum class PLAInputFunctorForMouse : PLAInputFunctor
{
  Press, Release, ReleaseOnOutSide, Move, Drag, DragOver, DragOut,
  kNumberOfItems, None = kGRAIntUndefined,
};

enum class PLAInputFunctorForKey : PLAInputFunctor
{
  Press, Release,
  kNumberOfItems, None = kGRAIntUndefined
};

using PLAInputCode = GRAInt;
static const GRAInt kPLAInputCodeUndefined = kGRAIntUndefined;

enum class PLAInputCodeForTouch : PLAInputCode
{
  _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
  kNumberOfItems, None = kGRAIntUndefined,
};

// マウスは何も押さずに画面上を移動させられるため移動時は常にNoneを送出する
// Noneは他のキーが押されていてもいなくても送出されるので、Handler側で処理を分ける
enum class PLAInputCodeForMouse : PLAInputCode
{ Left, Middle, Right, kNumberOfItems, None = kGRAIntUndefined };

enum class PLAInputCodeForKey : PLAInputCode
{
  _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  Esc, Tab, Return, Delete, Space, Shift, Control, Alt, Super,
  kNumberOfItems, None = kGRAIntUndefined,
};

#endif //PLAIN_ENGINE_PLAINPUTTYPE_HPP
