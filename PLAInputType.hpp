#ifndef PLAIN_ENGINE_PLAINPUTTYPE_HPP
#define PLAIN_ENGINE_PLAINPUTTYPE_HPP

#include "Plain.hpp"

enum class PLAInputDevice : int
{
  Touch,
  Mouse,
  Keyboard,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

enum class PLAInputCode : int
{
  Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
  A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
  Esc, Tab, Return, Delete, Space, Shift, Control, Alt, Super,
  MouseL, MouseM, MouseR, Touch,
  kNumberOfItems, None = kPLAIntUndefined,
};

enum class PLAInputState : int
{
  Up,
  Down,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //PLAIN_ENGINE_PLAINPUTTYPE_HPP
