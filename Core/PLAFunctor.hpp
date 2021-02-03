//
// Created by Kentaro Kawai on 2021/02/03.
//

#ifndef ANHR_PLAFUNCTOR_HPP
#define ANHR_PLAFUNCTOR_HPP

#include <functional>

template <typename T> class PLAFunctor
{
  std::function<void(T *)> _fOnInit = [](T *){};
  std::function<void(T *)> _fOnUpdate = [](T *){};
  std::function<void(T *)> _fOnAppear = [](T *){};
  std::function<void(T *)> _fOnDisappear = [](T *){};

public:
  PLAFunctor() {};
  ~PLAFunctor() {};

  void RunFunctorOnInit(T *aContext) { _fOnInit(aContext); };
  void RunFunctorOnUpdate(T *aContext) { _fOnUpdate(aContext); };
  void RunFunctorOnAppear(T *aContext) { _fOnAppear(aContext); };
  void RunFunctorOnDisappear(T *aContext) { _fOnDisappear(aContext); };

  void SetFunctorOnInit(const std::function<void(T *)> &aFunc)
  { _fOnInit = aFunc; };
  void SetFunctorOnUpdate(const std::function<void(T *)> &aFunc)
  { _fOnUpdate = aFunc; };
  void SetFunctorOnAppear(const std::function<void(T *)> &aFunc)
  { _fOnAppear = aFunc; };
  void SetFunctorOnDisappear(const std::function<void(T *)> &aFunc)
  { _fOnDisappear = aFunc; };
};


#endif //ANHR_PLAFUNCTOR_HPP
