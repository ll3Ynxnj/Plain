#ifndef ANHR_PLAIMAGETYPE_HPP
#define ANHR_PLAIMAGETYPE_HPP

enum class PLAImageType: PLAInt
{
  Raw,
  Jpg,
  Png,
  Pvr,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //ANHR_PLAIMAGETYPE_HPP
