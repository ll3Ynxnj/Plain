//
// Created by Kentaro Kawai on 2021/02/04.
//

#ifndef ANHR_PLALISTENER_HPP
#define ANHR_PLALISTENER_HPP

#include "PLAFunctor.hpp"

template <typename Context, typename Key> class PLAListener {
  PLAFunctor<Context, Key> _functor = PLAFunctor<Context, Key>();

public:
  void RunListener(Key aKey, Context *aContext)
  { _functor.RunFunction(aKey, aContext); }

  void SetListener(Key aKey,
                   const std::function<void(Context *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); }
};

#endif //ANHR_PLALISTENER_HPP
