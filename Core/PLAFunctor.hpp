//
// Created by Kentaro Kawai on 2021/02/03.
//

#ifndef ANHR_PLAFUNCTOR_HPP
#define ANHR_PLAFUNCTOR_HPP

#include <map>
#include <string>
#include <functional>
#include "PLAType.hpp"

template <typename Context, typename Key> class PLAFunctor
{
  std::map<Key, std::function<void(Context *)>> _functions =
    std::map<Key, std::function<void(Context *)>>();

public:
  PLAFunctor() {};
  ~PLAFunctor() {};

  void RunFunction(const Key &aKey, Context *aContext)
  {
    if (!_functions.contains(aKey)) { return; }
    _functions[aKey](aContext);
  }

  void SetFunction(const Key &aKey,
                   const std::function<void(Context *)> &aFunc)
  { _functions[aKey] = aFunc; }
};


#endif //ANHR_PLAFUNCTOR_HPP
