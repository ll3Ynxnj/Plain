#ifndef ANHR_PLAACTORFUNCTIONCODE_HPP
#define ANHR_PLAACTORFUNCTIONCODE_HPP

enum class PLAActorFunctionCode : PLAInt
{
  OnInit,
  OnUpdate,
  OnAppear,
  OnDisappear,

  kNumberOfItems,
  None = kPLAIntUndefined
};

#endif //ANHR_PLAACTORFUNCTIONCODE_HPP
