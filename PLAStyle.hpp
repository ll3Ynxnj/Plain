#ifndef PLAIN_PLASTYLE_HPP
#define PLAIN_PLASTYLE_HPP

#include <map>
#include <variant>
#include "Plain.hpp"
#include "PLAObject.hpp"
#include "PLAStyleType.hpp"
#include "PLAError.hpp"

class PLAStyle : public PLAObject
{
  struct Item
  {
    enum class Type
    {
      Int, Float, Color, kNumberOfItems, None
    };

    Type type = Type::None;
    union
    {
      int      intValue = 0;
      float    floatValue;
      PLAColor colorValue;
    };
  };

  static Item::Type kValidationTable[unsigned(PLAStyleType::kNumberOfItems)];
  std::map<PLAStyleType, Item> _items;

public:
  PLAStyle();
  virtual ~PLAStyle();

  int GetIntValue(PLAStyleType aType) const
  {
    if (!PLAStyle::IsValidItem(aType, Item::Type::Int))
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    };
    return _items.at(aType).intValue;
  };

  float GetFloatValue(PLAStyleType aType) const
  {
    if (!PLAStyle::IsValidItem(aType, Item::Type::Float))
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    };
    return _items.at(aType).floatValue;
  };

  const PLAColor &GetColorValue(PLAStyleType aType) const
  {
    if (!PLAStyle::IsValidItem(aType, Item::Type::Color))
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    };
    return _items.at(aType).colorValue;
  };

  void SetIntValue(PLAStyleType aType, const int &aValue)
  {
    if (PLAStyle::IsValidItem(aType, Item::Type::Int))
    { _items[aType].intValue = aValue; }
    else
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    }
  }

  void SetFloatValue(PLAStyleType aType, const float &aValue)
  {
    if (PLAStyle::IsValidItem(aType, Item::Type::Float))
    { _items[aType].floatValue = aValue; }
    else
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected value type.");
    }
  }

  void SetColorValue(PLAStyleType aType, const PLAColor &aValue)
  {
    if (PLAStyle::IsValidItem(aType, Item::Type::Color))
    { _items[aType].colorValue = aValue; }
    else
    {
      PLA_ERROR_ISSUE(PLAErrorType::Assert,
                      "Detected unexpected value type."); }
  }

private:
  static bool IsValidItem(PLAStyleType aType, Item::Type aValueType)
  { return kValidationTable[unsigned(aType)] == aValueType; };
};

#endif // PLAIN_PLASTYLE_HPP
