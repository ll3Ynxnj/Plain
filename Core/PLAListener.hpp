//
// Created by Kentaro Kawai on 2021/02/04.
//

#ifndef ANHR_PLALISTENER_HPP
#define ANHR_PLALISTENER_HPP

#include "PLAFunctor.hpp"

template <typename T> class PLAListener {
  PLAFunctor<T> _functor = PLAFunctor<T>();

public:
  void RunFunctionOfListener(const std::string &aKey, T *aContext)
  { _functor.RunFunction(aKey, aContext); }

  void SetFunctionOfListener(const std::string &aKey,
                             const std::function<void(T *)> &aFunc)
  { _functor.SetFunction(aKey, aFunc); }
};

#endif //ANHR_PLALISTENER_HPP
