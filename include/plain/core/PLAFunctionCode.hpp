//
// Created by Kentaro Kawai on 2023/04/19.
//

#ifndef ANHR_PLAFUNCTIONCODE_HPP
#define ANHR_PLAFUNCTIONCODE_HPP


#include "plain/core/primitive/PLAPRMType.hpp"

//using PLAFunctionCode = PLAUInt;
//static const PLAFunctionCode kPLAFunctionCodeNone = kPLAUIntUndefined;

namespace PLAFunctionCode
{
  using Code = PLAUInt;

  static const Code kNone = kPLAUIntUndefined;

  enum class App : Code
  {
    //OnInit,
    OnUpdate,

    kNumberOfItems,
    None = kNone,
  };

  enum class Actor : Code
  {
    OnUpdate,
    OnAppear,
    OnDisappear,

    kNumberOfItems,
    None = kNone,
  };

  enum class Phase : Code
  {
    OnPushed,
    OnPopped,

    OnPushedOver,
    OnPoppedOver,

    OnPushChild,
    OnPopChild,

    kNumberOfItems,
    None = kNone,
  };

  enum class Scene: Code
  {
    //OnUpdate,

    kNumberOfItems,
    None = kNone,
  };

  enum class Stage : Code
  {
    //OnUpdate,
    OnResize,

    kNumberOfItems,
    None = kNone,
  };

  enum class Timeline: Code
  {
    OnStart,  ///< \~english Runs before first update. \~japanese 初回の更新より前に実行。
    OnUpdate, ///< \~english Runs on every update. \~japanese 毎回の更新時に実行。
    OnStop,   ///< \~english Runs after last update. \~japanese 最後の更新より後に実行。
    OnDestroy,///< \~english Runs when timeline is destroyed. \~japanese タイムラインが破棄されるときに実行。

    kNumberOfItems,
    None = kNone,
  };

  enum class TimelineNode: Code
  {
    OnStart,  ///< \~english Runs before first update. \~japanese 初回の更新より前に実行。
    OnUpdate, ///< \~english Runs on every update. \~japanese 毎回の更新時に実行。
    OnStop,   ///< \~english Runs after last update. \~japanese 最後の更新より後に実行。

    kNumberOfItems,
    None = kNone,
  };
};


#endif //ANHR_PLAFUNCTIONCODE_HPP
