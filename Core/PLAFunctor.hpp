//
// Created by Kentaro Kawai on 2021/02/03.
//

#ifndef ANHR_PLAFUNCTOR_HPP
#define ANHR_PLAFUNCTOR_HPP

#include <map>
#include <string>
#include <functional>
#include "PLAType.hpp"

template <typename T> class PLAFunctor
{
  std::map<std::string, std::function<void(T *)>> _functions =
    std::map<std::string, std::function<void(T *)>>();

public:
  PLAFunctor() {};
  ~PLAFunctor() {};

  void RunFunction(const std::string &aKey, T *aContext)
  {
    if (!_functions.contains(aKey)) { return; }
    _functions[aKey](aContext);
  }

  void SetFunction(const std::string &aKey,
                   const std::function<void(T *)> &aFunc)
  { _functions[aKey] = aFunc; }
};


#endif //ANHR_PLAFUNCTOR_HPP
