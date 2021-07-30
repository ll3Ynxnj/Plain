#ifndef PLAIN_PLAIMAGETYPE_HPP
#define PLAIN_PLAIMAGETYPE_HPP

enum class PLAImageType: PLAInt
{
  Raw,
  Jpg,
  Png,
  Pvr,

  kNumberOfItems,
  None = kPLAIntUndefined,
};

#endif //PLAIN_PLAIMAGETYPE_HPP
