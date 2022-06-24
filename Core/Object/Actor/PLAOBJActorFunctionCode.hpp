#ifndef PLAIN_PLAACTORFUNCTIONCODE_HPP
#define PLAIN_PLAACTORFUNCTIONCODE_HPP

enum class PLAOBJActorFunctionCode : PLAInt
{
  OnInit,
  OnUpdate,
  OnAppear,
  OnDisappear,

  kNumberOfItems,
  None = kPLAIntUndefined
};

#endif //PLAIN_PLAACTORFUNCTIONCODE_HPP
