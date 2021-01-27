#ifndef PLAIN_ENGINE_PLASTYLE_HPP
#define PLAIN_ENGINE_PLASTYLE_HPP

#include <map>
#include <variant>
#include "PLAType.hpp"
#include "PLAObject.hpp"
#include "PLAStyleType.hpp"

class PLAStyle : public PLAObject
{
public:
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

  int GetIntValue(PLAStyleType aType) const;
  float GetFloatValue(PLAStyleType aType) const;
  const PLAColor &GetColorValue(PLAStyleType aType) const;
  void SetIntValue(PLAStyleType aType, const int &aValue);
  void SetFloatValue(PLAStyleType aType, const float &aValue);
  void SetColorValue(PLAStyleType aType, const PLAColor &aValue);

private:
  static bool IsValidItem(PLAStyleType aType, Item::Type aValueType)
  { return kValidationTable[unsigned(aType)] == aValueType; };
};

#endif // PLAIN_ENGINE_PLASTYLE_HPP
