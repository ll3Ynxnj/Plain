#ifndef PLAIN_PLASTYLE_HPP
#define PLAIN_PLASTYLE_HPP

#include <map>
#include <variant>
#include "Plain.hpp"
#include "PLAStyleType.hpp"
#include "PLAErrorManager.hpp"

class PLAStyle
{
  struct Item
  {
    enum class Type
    {
      Int, Float, Color, kNumberOfItems, None
    };

    Type type = Type::None;
    union Value
    {
      int      i = 0;
      float    f;
      PLAColor color;
    } value;
  };

  static Item::Type kValidationTable[unsigned(PLAStyleType::kNumberOfItems)];
  std::map<PLAStyleType, Item> _items;

public:
  PLAStyle();
  virtual ~PLAStyle();

  template <typename T> const T &GetValue(PLAStyleType aType) const
  { PLAError::Throw(PLAErrorType::Assert,
                    "Detected unexpected value type."); };
  template <> const int &GetValue(PLAStyleType aType) const
  { return _items.at(aType).value.i; };
  template <> const float &GetValue(PLAStyleType aType) const
  { return _items.at(aType).value.f; };
  template <> const PLAColor &GetValue(PLAStyleType aType) const
  { return _items.at(aType).value.color; };

  template <typename T> void SetValue(PLAStyleType aType, const T &aValue)
  {
    PLAError::Throw(PLAErrorType::Assert,
                    "Detected unexpected value type.");
  }

  template <> void SetValue(PLAStyleType aType, const int &aValue)
  {
    if (PLAStyle::IsValidItem(aType, Item::Type::Int))
    { _items[aType].value.i = aValue; }
    else
    {
      PLAError::Throw(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    }
  }

  template <> void SetValue(PLAStyleType aType, const float &aValue)
  {
    if (PLAStyle::IsValidItem(aType, Item::Type::Float))
    { _items[aType].value.f = aValue; }
    else
    {
      PLAError::Throw(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    }
  }

  template <> void SetValue(PLAStyleType aType, const PLAColor &aValue)
  {
    if (PLAStyle::IsValidItem(aType, Item::Type::Color))
    { _items[aType].value.color = aValue; }
    else
    {
      PLAError::Throw(PLAErrorType::Assert,
                      "Detected unexpected value type."); }
  }

private:
  static bool IsValidItem(PLAStyleType aType, Item::Type aValueType)
  { return kValidationTable[unsigned(aType)] == aValueType; };
};

#endif // PLAIN_PLASTYLE_HPP
