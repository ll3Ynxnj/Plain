#include "PLAStyle.hpp"
#include "PLAError.hpp"

PLAStyle::Item::Type PLAStyle::kValidationTable[unsigned(PLAStyleType::kNumberOfItems)]
{
  PLAStyle::Item::Type::Color, // FillColor
  PLAStyle::Item::Type::Color, // StrokeColor
  PLAStyle::Item::Type::Float, // StrokeWidth
};

PLAStyle::PLAStyle() :
PLAObject(PLAObjectType::Style)
{

}

PLAStyle::~PLAStyle()
{

}

int PLAStyle::GetIntValue(PLAStyleType aType) const
{
  if (!PLAStyle::IsValidItem(aType, Item::Type::Int))
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Detected unexpected value type.");
  };
  return _items.at(aType).intValue;
};

float PLAStyle::GetFloatValue(PLAStyleType aType) const
{
  if (!PLAStyle::IsValidItem(aType, Item::Type::Float))
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Detected unexpected value type.");
  };
  return _items.at(aType).floatValue;
};

const PLAColor &PLAStyle::GetColorValue(PLAStyleType aType) const
{
  if (!PLAStyle::IsValidItem(aType, Item::Type::Color))
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Detected unexpected value type.");
  };
  return _items.at(aType).colorValue;
};

void PLAStyle::SetIntValue(PLAStyleType aType, const int &aValue)
{
  if (PLAStyle::IsValidItem(aType, Item::Type::Int))
  { _items[aType].intValue = aValue; }
  else
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Detected unexpected value type.");
  }
}

void PLAStyle::SetFloatValue(PLAStyleType aType, const float &aValue)
{
  if (PLAStyle::IsValidItem(aType, Item::Type::Float))
  { _items[aType].floatValue = aValue; }
  else
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Detected unexpected value type.");
  }
}

void PLAStyle::SetColorValue(PLAStyleType aType, const PLAColor &aValue)
{
  if (PLAStyle::IsValidItem(aType, Item::Type::Color))
  { _items[aType].colorValue = aValue; }
  else
  {
    PLA_ERROR_ISSUE(PLAErrorType::Assert,
                    "Detected unexpected value type."); }
}
